# PerceptronBPred
Perceptron Branch Prediction for gem5

## Contents
* src/cpu/pred
  * `perceptron_local.*`
  * `perceptron.hh`
  * `BranchPredictor.py`
  * `SConscript`
* build/X86/params
  * `PerceptronLocalBP.hh`
* configs/example
  * `se.py`
  
## Instructions
1. Implement PerceptronLocalBP branch predictor class in `perceptron_local.*`
2. Add struct for desired parameters in `PerceptronLocalBP.hh`
3. Implement individual perceptron units in `perceptron.hh`
4. Add source file in `SConscript`
5. Add corresponding branch predictor class in `BranchPredictor.py`
6. Modify `se.py` to select the PerceptronLocalBP branch predictor for CPU(s)
