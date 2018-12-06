#include "cpu/pred/perceptron_local.hh"

#include "base/intmath.hh"
#include "base/logging.hh"
#include "base/trace.hh"
#include "debug/Fetch.hh"
#include "base/bitfield.hh"

PerceptronLocalBP::PerceptronLocalBP(const PerceptronLocalBPParams *params)
    : BPredUnit(params),
      localPerceptronSize(params->localPercepSize),
	  localPredictorSets(params->localPredictorSize)
{

	// Setup the index mask.
	indexMask = localPredictorSets - 1;
	
	DPRINTF(Fetch, "index mask: %#x\n", indexMask);

	//Setup the array of perceptrons for the local predictor
	localPerceps.resize(localPredictorSets);
	
    for (size_t i = 0; i < localPredictorSets; ++i) {
		localPerceps[i].setSize(localPerceptronSize);
	}
	
	DPRINTF(Fetch, "local predictor sets: %i\n", localPredictorSets);

    DPRINTF(Fetch, "local perceptron size: %i\n",
            localPerceptronSize);
			
}

void
PerceptronLocalBP::reset()
{
    for (size_t i = 0; i < localPredictorSets; ++i) {
        localPerceps[i].reset();
    }
}

void
PerceptronLocalBP::btbUpdate(ThreadID tid, Addr branch_addr, void * &bp_history)
{
// Place holder for a function that is called to update predictor history when
// a BTB entry is invalid or not found.
}


bool
PerceptronLocalBP::lookup(ThreadID tid, Addr branch_addr, void * &bp_history)
{
    bool taken;
    int counter_val;
    size_t local_predictor_idx = getLocalIndex(branch_addr);

    DPRINTF(Fetch, "Looking up index %#x\n",
            local_predictor_idx);

    counter_val = localPerceps[local_predictor_idx].read(globalHistory);

    DPRINTF(Fetch, "prediction is %i.\n",
            counter_val);

    taken = getPrediction(counter_val);

#if 0
    // Speculative update.
    if (taken) {
        DPRINTF(Fetch, "Branch updated as taken.\n");
        updateGlobalHistTaken(tid);
    } else {
        DPRINTF(Fetch, "Branch updated as not taken.\n");
        updateGlobalHistNotTaken(tid);
    }
#endif

    return taken;
}

void
PerceptronLocalBP::update(ThreadID tid, Addr branch_addr, bool taken, void *bp_history,
                bool squashed)
{
    assert(bp_history == NULL);
    size_t local_predictor_idx;

    // No state to restore, and we do not update on the wrong
    // path.
    if (squashed) {
        return;
    }

    // Update the local predictor.
    local_predictor_idx = getLocalIndex(branch_addr);

    DPRINTF(Fetch, "Looking up index %#x\n", local_predictor_idx);
	
	localPerceps[local_predictor_idx].train(taken);

    if (taken) {
        DPRINTF(Fetch, "Branch updated as taken.\n");
        updateGlobalHistTaken(tid);
    } else {
        DPRINTF(Fetch, "Branch updated as not taken.\n");
        updateGlobalHistNotTaken(tid);
    }
}

void
PerceptronLocalBP::uncondBranch(ThreadID tid, Addr pc, void *&bp_history)
{
}

PerceptronLocalBP*
PerceptronLocalBPParams::create()
{
    return new PerceptronLocalBP(this);
}

bool
PerceptronLocalBP::getPrediction(int count)
{
    // Round the perceptron output and convert to boolean
    return (count > 0) ? true : false;
}

size_t
PerceptronLocalBP::getLocalIndex(Addr &branch_addr)
{
    return (branch_addr >> instShiftAmt) & indexMask;
}

void
PerceptronLocalBP::updateGlobalHistTaken(ThreadID tid)
{
    globalHistory = (globalHistory << 1) | 1;
//    globalHistory[tid] = globalHistory[tid] & historyRegisterMask;
}

void
PerceptronLocalBP::updateGlobalHistNotTaken(ThreadID tid)
{
    globalHistory = (globalHistory << 1);
//    globalHistory[tid] = globalHistory[tid] & historyRegisterMask;
}
