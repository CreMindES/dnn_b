/**
 * @brief       Homework project
 * @author      Tamás G. Barna < tamas.g.barna@gmail.com >
 */

#ifndef LAYER_H
#define LAYER_H

#include <functional>
#include <string>
#include <vector>

#include "neuron.h"
#include "matrix.h"

using namespace std;

class Layer
{
  public:
    Layer( const uint32_t neuronNumber, function< double (const double&)> activationFunction,
           function< Matrix<double> (const Matrix<double>&, const Matrix<double>&)> backwardActivationFunction, const string& name = "" ) :
        isFirst( false ),
        neuronNum( neuronNumber ),
        actFunction( activationFunction ),
        backwardActFunction( backwardActivationFunction ),
        m_name( name )
    {

    }

    void setFirst() { isFirst = true; }
    void init( const unsigned& inputDim, const unsigned& outputDim );

    Matrix<double> forward( const Matrix<double>& input );
    void backward( Layer* nextLayer = nullptr );

    size_t inline getNeuronCount() const { return neuronNum; }
    function< double (const double&)> getActFunction() const { return actFunction; }
    inline Matrix<double>& getOutput() { return output; }

    inline Matrix<double> getdA() const { return dA; }
    inline void setdA( const Matrix<double>& m ) { dA = m; }
    inline Matrix<double> getdZ() const { return dZ; }

    void update( const double& learningRate );

    friend class Test;

private:
    bool isFirst;
    unsigned neuronNum;
    function< double (const double&)> actFunction;
    function< Matrix<double> (const Matrix<double>&, Matrix<double>&)> backwardActFunction;
    string m_name;

    Matrix<double> weight;
    Matrix<double> bias;

    Matrix<double> input;
    Matrix<double> Z;
    Matrix<double> output;  // usually called A

    Matrix<double> dA;
    Matrix<double> dZ;
    Matrix<double> dWeight;
    Matrix<double> dBias;
};

#endif // LAYER_H
