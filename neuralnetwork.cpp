/**
 * @brief       Homework project
 * @author      Tamás G. Barna < tamas.g.barna@gmail.com >
 */

#include "neuralnetwork.h"

NeuralNetwork::NeuralNetwork()
{

}

void NeuralNetwork::addLayer(Layer* layer)
{
    if( layer == nullptr ) { return; }
    if( layerVect.size() == 0 ) { layer->setFirst(); }

    layerVect.push_back( layer );
}

void NeuralNetwork::train(const Matrix<double>& input, const Matrix<double>& groundTruth, const double& learningRate, const unsigned& iterNumber )
{
#ifdef DEBUG
    cout << "input:" << endl << input << endl
         << "output" << endl << groundTruth << endl;
#endif

    // init weights in layers
    for( size_t layerIndex = 1; layerIndex < layerVect.size(); ++layerIndex ) {
        Layer* layer = layerVect.at( layerIndex );
        Layer* prevLayer = layerVect.at( layerIndex - 1 );
        layer->init( layer->getNeuronCount(), prevLayer->getNeuronCount() );
    }

    for( unsigned i = 0; i < iterNumber; ++i ) {
        // TODO: add  dropout

        feedForward( input );
        backPropagate( groundTruth );
        update( learningRate );

        // report cost function periodically
        if( i % static_cast<unsigned>(iterNumber/10) == 0 ) {
            double cost = calcCost( layerVect.back()->getOutput(), groundTruth );
            cout << "Iter: " << i << " | Cost: " << cost << endl;
        }

        // TODO: early stopping
    }

    cout << endl << "last output:" << layerVect.back()->getOutput() << endl;

    cout << endl << "Done" << endl;

}

Matrix<double> NeuralNetwork::feedForward( const Matrix<double>& input )
{
    if( layerVect.size() == 0 ) {
        // TODO: handle error
        return Matrix<double>();
    }

    Matrix<double> result( input );
    result = layerVect.at(0)->forward( input );

    // TODO: possibly this can be transformed into tail recursive call
    for( size_t layerIndex = 1; layerIndex < layerVect.size(); ++layerIndex ) {
        result = layerVect.at(layerIndex)->forward( result );
        // cout << "result" << endl << result << endl;
    }

    return( result );
}

void NeuralNetwork::backPropagate( const Matrix<double>& groundTruth )
{
    Layer* lastLayer = layerVect.back();

    assert( lastLayer->getOutput().size() == groundTruth.size() );

    // do backprop part 1 manually for last layer
    // derivative of cost with respect to last layer's output
    lastLayer->setdA( -1 * ( ( groundTruth / lastLayer->getOutput() ) - ((1 - groundTruth) / (1 - lastLayer->getOutput() )) ) );

    // back propagation
    for( size_t layerIndex = layerVect.size()-1; layerIndex > 0; --layerIndex ) {
        Layer* layer     = layerVect.at(layerIndex);
        Layer* prevLayer = layerVect.at(layerIndex-1);

        layer->backward( prevLayer );
    }
}

void NeuralNetwork::update(const double& learningRate)
{
    for( size_t layerIndex = 1; layerIndex < layerVect.size(); ++layerIndex ) {
        Layer* layer = layerVect.at( layerIndex );
        layer->update( learningRate );
    }
}

double NeuralNetwork::calcCost( const Matrix<double>& output, const
                            Matrix<double>& groundTruth )
{
    double m = output.size().column;
    return (-1 / m) * ( groundTruth * output.log() + ((1 - groundTruth) * ((1 - output).log())) ).rowSum().toDouble();
}
