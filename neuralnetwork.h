/**
 * @brief       Homework project
 * @author      Tamás G. Barna < tamas.g.barna@gmail.com >
 */

#ifndef NEURALNETWORK_H
#define NEURALNETWORK_H

#include <algorithm>
#include <assert.h>
#include <functional>
#include <iostream>
#include <math.h>
#include <random>
#include <vector>

#include "layer.h"
#include "matrix.h"

#define DEBUG

using namespace std;

class NeuralNetwork
{
public:
    NeuralNetwork();
    void addLayer( Layer* layer );
    void train(const Matrix<double>& input, const Matrix<double>& groundTruth, const double& learningRate = 0.1, const unsigned& iterNumber = 100);
    vector<double> predict( const vector<double>& inputVect );

private:
    Matrix<double> feedForward( const Matrix<double>& input );
    void backPropagate( const Matrix<double>& groundTruth );

private:
    std::vector< Layer* > layerVect;
};

#endif // NEURALNETWORK_H
