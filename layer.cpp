/**
 * @brief       Homework project
 * @author      Tamás G. Barna < tamas.g.barna@gmail.com >
 */

#include "layer.h"

/**
 * @brief Layer::init initializez weights and bias vector of the layer
 * @param inputDim
 * @param outputDim
 */
void Layer::init( const unsigned& inputDim, const unsigned& outputDim )
{
    weight.resize( inputDim, outputDim );
    weight.fill( 0, 20 );

    bias.resize( inputDim, 1 );
    bias.fill( 0 );

    // cout << "weight" << endl << weight << endl;
}

/**
 * @brief Layer::forward forward propagation
 * @param input input from previous layer or input from outside the network in case of the first layer
 * @return the output of the layer after neuron activations. note: this output is also cached locally
 */
Matrix<double> Layer::forward( const Matrix<double>& input )
{
    this->input = input;

    // first layer is represented like any other layer for education and code cleaness purposes.
    // hence it is just a pass trough layer, we just take the input to the output side.
    // later could be further uniformed with an identity weight matrix and 0 bias vector
    if( isFirst ) {
        Z      = input;
        output = input;
        return input;
    } // TODO

    Z = Matrix<double>::dot( weight, input ) + bias;
    output = Z;  // copy
    output.apply( actFunction );

    // cout << "Z:" << endl << Z << "output" << endl << output << endl;

    return output;
}

/**
 * @brief Layer::backward backpropagation -> gradients
 * @param prevLayer pointer to previous layer in the network
 */
void Layer::backward( Layer* prevLayer )
{
    // backward activation
    dZ = backwardActFunction( dA, Z );

    unsigned m = prevLayer->getOutput().size().column;

    // calculate gradients
    dWeight = Matrix<double>::dot( dZ, prevLayer->getOutput().transpose() ) / m;
    dBias   = dZ.rowSum() / m;
    prevLayer->dA = Matrix<double>::dot( weight.transpose(), dZ );
}

/**
 * @brief Layer::update updates the learning parameters weight and bias to converge error minimum
 * @param learningRate rate of learning
 */
void Layer::update( const double& learningRate )
{
    weight = weight - ( learningRate * dWeight );
    bias   = bias   - ( learningRate * dBias   );
}
