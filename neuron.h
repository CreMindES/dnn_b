/**
 * @brief       Homework project
 * @author      Tamás G. Barna < tamas.g.barna@gmail.com >
 */

#ifndef NEURON_H
#define NEURON_H

#include <math.h>

#include "matrix.h"

#define UNUSED(expr) do { (void)(expr); } while (0)

class Neuron
{
  public:

    static inline double sigmoid( double x )
    {
        return 1 / ( 1 + exp(-x) );
    }

    static inline Matrix<double> sigmoidBackward( const Matrix<double>& dA, const Matrix<double>& Z )
    {
        Matrix<double> s = 1 / ( ( -1 * Z ).exp() + 1);
        Matrix<double> dZ = dA * s * (1-s);

        return dZ;
    }

    static inline double relu( double x ) {
        return x > 0 ? x : 0;
    }

    static inline Matrix<double> reluBackward( const Matrix<double>& dA, const Matrix<double>& Z ) { UNUSED(dA);
        return Z.nonNegative();
    }

    static inline double dummy( double x ) {
        return x;
    }

  private:

    Neuron() { }
};

#endif // NEURON_H
