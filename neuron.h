/**
 * @brief       Homework project
 * @author      Tamás G. Barna < tamas.g.barna@gmail.com >
 */

#ifndef NEURON_H
#define NEURON_H

#include <math.h>

class Neuron
{
  public:

    static inline double sigmoid( double x, const bool deriv = false )
    {
        if( deriv ) return exp(-x) / ( (1+exp(-x)) * (1+exp(-x)) );
        else return 1 / ( 1 + exp(-x) );
    }

    static inline double relu( double x, const bool deriv = false ) {
        if ( deriv ) return x > 0 ? 1 : 0;
        else return x > 0 ? x : 0;
    }

    static inline double dummy( double x, const bool deriv = false ) {
        return deriv ? x : x;
    }

  private:

    Neuron() { }
};

#endif // NEURON_H
