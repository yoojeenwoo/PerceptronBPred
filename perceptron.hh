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
    Perceptron()
        : initialVal(0), counter(0)
    { }

    /**
     * Constructor for the perceptron.
     * @param bits How many bits the counter will have.
     */
    Perceptron(unsigned bits)
        : initialVal(0), maxVal((1 << bits) - 1), counter(0)
    { }

    /**
     * Constructor for the counter.
     * @param bits How many bits the counter will have.
     * @param initial_val Starting value for each counter.
     */
    Perceptron(unsigned bits, uint8_t initial_val)
        : initialVal(initial_val), maxVal((1 << bits) - 1),
          counter(initial_val)
    {
        // Check to make sure initial value doesn't exceed the max
        // counter value.
        if (initial_val > maxVal) {
            fatal("BP: Initial counter value exceeds max size.");
        }
    }

    /**
     * Sets the number of bits.
     */
    void setBits(unsigned bits) { maxVal = (1 << bits) - 1; }

    void reset() { counter = initialVal; }

    /**
     * Read the counter's value.
     */
    uint8_t read() const
    { return counter; }

  private:
	std::vector<int> weights;
    
};

#endif // __PERCEPTRON_HH__