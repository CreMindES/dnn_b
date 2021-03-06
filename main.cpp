/**
 * @brief       Homework project
 * @author      Tamás G. Barna < tamas.g.barna@gmail.com >
 */

#include <iostream>
#include <vector>

// #include "eigen/Eigen/Dense"

#include "layer.h"
#include "matrix.h"
#include "neuralnetwork.h"
#include "neuron.h"

#include "test.h"

using namespace std;

int main()
{
//    run_tests();
//    return 0;

    // example input
    Matrix<double> input( 3, 4 );
    input.setColumn( 1, vector<double>{ 0, 0, 1 } );
    input.setColumn( 2, vector<double>{ 0, 1, 1 } );
    input.setColumn( 3, vector<double>{ 1, 0, 1 } );
    input.setColumn( 4, vector<double>{ 1, 1, 1 } );

    // example output
    Matrix<double> output(1, 4);
    output.setRow(1, vector<double>{ 0, 1, 1, 0 } );

    // create a new NN
    NeuralNetwork* myNetwork = new NeuralNetwork();
    // set up topology
    myNetwork->addLayer( new Layer( 3, Neuron::dummy, nullptr, "input" ) );
    // myNetwork->addLayer( new Layer( 3, Neuron::relu, Neuron::reluBackward, "hidden" ) );
    myNetwork->addLayer( new Layer( 3, Neuron::sigmoid, Neuron::sigmoidBackward, "hidden" ) );
    myNetwork->addLayer( new Layer( 1, Neuron::sigmoid, Neuron::sigmoidBackward, "output" ) );
    // train
    myNetwork->train( input, output, 0.01, 30000 );

    // predict
    // myNetwork->predict( inputTest )

    return 0;
}


