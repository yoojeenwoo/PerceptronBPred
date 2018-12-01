#ifndef __PERCEPTRON_HH__
#define __PERCEPTRON_HH__

#include "base/logging.hh"
#include "base/types.hh"

/**
 * Private perceptron class
 * Implements a perceptron
 */
class Perceptron
{
  public:
    /**
     * Constructor for the perceptron.
     */
    Perceptron() : N(1)
    { std::vector<int> weights(N, 0); }

    /**
     * Constructor for the perceptron.
     * @param units How many input neurons the perceptron will have
     */
    Perceptron(size_t units)
        : N(units)
    { std::vector<int> weights(N, 0); }

    /**
     * Constructor for the perceptron.
     * @param units How many input neurons the perceptron will have
     * @param initial_w Initial value of each weight
     */
    Perceptron(size_t units, int initial_w)
        : N(units)
    { std::vector<int> weights(N, initial_w); }

    /**
     * Sets the number of input neurons
     */
    void setSize(size_t _N) { N = _N; }

    void reset() { counter = initialVal; }

    /**
     * Read the counter's value.
     */
    uint8_t read(const BPHistory& hist) const { 
		int sum = 0;
		for (size_t i = 0; i < N; ++i) {
			if ((hist.globalHistory >> i) & 1) {
				sum += weights[i];
			} else {
				sum -= weights[i];
			}
		}
		return sum;
	}
	

  private:
	size_t N; // Size of perceptron
	std::vector<int> weights; 
    
};

#endif // __PERCEPTRON_HH__