#include "cpu/pred/perceptron_local.hh"

#include "base/intmath.hh"
#include "base/logging.hh"
#include "base/trace.hh"
#include "debug/Fetch.hh"
#include "base/bitfield.hh"

LocalBP::LocalBP(const LocalBPParams *params)
    : BPredUnit(params),
      localPredictorSize(params->localPredictorSize),
      localCtrBits(params->localCtrBits)
{
    if (!isPowerOf2(localPredictorSize)) {
        fatal("Invalid local predictor size!\n");
    }

    localPredictorSets = localPredictorSize / localCtrBits;

    if (!isPowerOf2(localPredictorSets)) {
        fatal("Invalid number of local predictor sets! Check localCtrBits.\n");
    }

    // Setup the index mask.
    indexMask = localPredictorSets - 1;

    DPRINTF(Fetch, "index mask: %#x\n", indexMask);

    // Setup the array of counters for the local predictor.
    localCtrs.resize(localPredictorSets);

    for (unsigned i = 0; i < localPredictorSets; ++i)
        localCtrs[i].setBits(localCtrBits);

    DPRINTF(Fetch, "local predictor size: %i\n",
            localPredictorSize);

    DPRINTF(Fetch, "local counter bits: %i\n", localCtrBits);

    DPRINTF(Fetch, "instruction shift amount: %i\n",
            instShiftAmt);
}

void
LocalBP::reset()
{
    for (unsigned i = 0; i < localPredictorSets; ++i) {
        localCtrs[i].reset();
    }
}

void
LocalBP::btbUpdate(ThreadID tid, Addr branch_addr, void * &bp_history)
{
// Place holder for a function that is called to update predictor history when
// a BTB entry is invalid or not found.
}


bool
LocalBP::lookup(ThreadID tid, Addr branch_addr, void * &bp_history)
{
    bool taken;
    uint8_t counter_val;
    unsigned local_predictor_idx = getLocalIndex(branch_addr);

    DPRINTF(Fetch, "Looking up index %#x\n",
            local_predictor_idx);

    counter_val = localCtrs[local_predictor_idx].read();

    DPRINTF(Fetch, "prediction is %i.\n",
            (int)counter_val);

    taken = getPrediction(counter_val);

#if 0
    // Speculative update.
    if (taken) {
        DPRINTF(Fetch, "Branch updated as taken.\n");
        localCtrs[local_predictor_idx].increment();
        updateGlobalHistTaken(tid);
    } else {
        DPRINTF(Fetch, "Branch updated as not taken.\n");
        localCtrs[local_predictor_idx].decrement();
        updateGlobalHistNotTaken(tid);
    }
#endif

    return taken;
}

void
LocalBP::update(ThreadID tid, Addr branch_addr, bool taken, void *bp_history,
                bool squashed)
{
    assert(bp_history == NULL);
    unsigned local_predictor_idx;

    // No state to restore, and we do not update on the wrong
    // path.
    if (squashed) {
        return;
    }

    // Update the local predictor.
    local_predictor_idx = getLocalIndex(branch_addr);

    DPRINTF(Fetch, "Looking up index %#x\n", local_predictor_idx);

    if (taken) {
        DPRINTF(Fetch, "Branch updated as taken.\n");
        localCtrs[local_predictor_idx].increment();
    } else {
        DPRINTF(Fetch, "Branch updated as not taken.\n");
        localCtrs[local_predictor_idx].decrement();
    }
}

inline
bool
LocalBP::getPrediction(uint8_t &count)
{
    // Round the perceptron output and convert to boolean
    return (count >> (localCtrBits - 1));
}

inline
unsigned
LocalBP::getLocalIndex(Addr &branch_addr)
{
    return (branch_addr >> instShiftAmt) & indexMask;
}

void
LocalBP::uncondBranch(ThreadID tid, Addr pc, void *&bp_history)
{
}

LocalBP*
LocalBPParams::create()
{
    return new LocalBP(this);
}

inline
void
LocalBP::updateGlobalHistTaken(ThreadID tid)
{
    globalHistory[tid] = (globalHistory[tid] << 1) | 1;
//    globalHistory[tid] = globalHistory[tid] & historyRegisterMask;
}

inline
void
LocalBP::updateGlobalHistNotTaken(ThreadID tid)
{
    globalHistory[tid] = (globalHistory[tid] << 1);
//    globalHistory[tid] = globalHistory[tid] & historyRegisterMask;
}
