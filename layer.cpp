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

void Layer::backward( Layer* prevLayer )
{
    // TODO: add regularization

    if( dA.size().row == 0 ) {  // not last layer
        //  derivative of cost with respect to layer's output
        dA = -1 * ( ( prevLayer->getOutput() / this->getOutput() ) - ((1 - prevLayer->getOutput()) / (1 - this->getOutput() )) );
    }
    // backward activation
    dZ = backwardActFunction( dA, Z );

//     cout << "dZ" << endl << dZ << endl << endl;

    unsigned m = prevLayer->getOutput().size().column;

    dWeight = Matrix<double>::dot( dZ, prevLayer->getOutput().transpose() ) / m;
    dBias   = dZ.rowSum() / m;
    prevLayer->dA = Matrix<double>::dot( weight.transpose(), dZ );

//    cout << dWeight << endl
//         << dBias << endl
//         << prevLayer->dA << endl;

}
