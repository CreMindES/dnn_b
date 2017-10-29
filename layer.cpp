/**
 * @brief       Homework project
 * @author      Tamás G. Barna < tamas.g.barna@gmail.com >
 */

#include "layer.h"

void Layer::init(const unsigned& inputDim, const unsigned& outputDim)
{
    weight.resize( inputDim, outputDim );
    weight.fill( 0.01, 0.005 );

    bias.resize( inputDim, 1 );
    bias.fill( 0 );

    // cout << "weight" << endl << weight << endl;
}

Matrix<double> Layer::forward(const Matrix<double>& input)
{
    this->input = input;

    if( isFirst ) { return input; } // TODO

    Z = Matrix<double>::dot( weight, input ) + bias;
    output = Z;
    output.apply( actFunction );

    // cout << "Z:" << end << Z << "output" << endl << output << endl;

    return output;
}

void Layer::backward(Layer* nextLayer, Matrix<double> dZ)
{
    if( nextLayer != nullptr ) {  // not last layer
        //  derivative of cost with respect to layer's output
        dA = -1 * ( ( nextLayer->getOutput() / this->getOutput() ) - ((1 - nextLayer->getOutput()) / (1 - this->getOutput() )) );
    }
    // backward activation
    dZ = dA;  // deep copy
    dZ.apply( actFunction, true );

    dWeight = Matrix<double>::dot( dZ, nextLayer->getOutput().transpose() ) / ((int)nextLayer->getOutput().size().row * -1);
    // dBias   =
}
