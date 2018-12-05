#ifndef __PARAMS__PerceptronLocalBP__
#define __PARAMS__PerceptronLocalBP__

class PerceptronLocalBP;

#include <cstddef>
#include "base/types.hh"
#include <cstddef>
#include "base/types.hh"

#include "params/BranchPredictor.hh"

struct PerceptronLocalBPParams
    : public BranchPredictorParams
{
    PerceptronLocalBP * create();
    unsigned localPercepSize;
    unsigned localPredictorSize;
};

#endif // __PARAMS__PerceptronLocalBP__