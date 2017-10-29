/**
 * @brief       Homework project
 * @author      Tamás G. Barna < tamas.g.barna@gmail.com >
 *
 * Note: most of the examples are taken from deeplearning.ai's Coursera course.
 */

#include "neuralnetwork.h"

class Test {

public:

    static bool model_forward() {
        Layer* layer0 = new Layer( 3, Neuron::dummy, nullptr );
        Layer* layer1 = new Layer( 3, Neuron::relu, Neuron::reluBackward );
        Layer* layer2 = new Layer( 1, Neuron::sigmoid, Neuron::sigmoidBackward );

        NeuralNetwork* nn = new NeuralNetwork();
        nn->addLayer( layer0 );
        nn->addLayer( layer1 );
        nn->addLayer( layer2 );

        Matrix<double> W1 = Matrix<double>( 3, 4 );
        W1.setRow( 1, std::vector<double>{  0.319039, -0.249370,  1.462107, -2.060140 } );
        W1.setRow( 2, std::vector<double>{ -0.322417, -0.384054,  1.133769, -1.099891 } );
        W1.setRow( 3, std::vector<double>{ -0.172428, -0.877858,  0.042213,  0.582815 } );

        Matrix<double> b1 = Matrix<double>( 3, 1 );
        b1.setColumn( 1, std::vector<double>{ -1.100619, 1.144723, 0.901590 } );

        Matrix<double> W2 = Matrix<double>( 1, 3 );
        W2.setRow( 1, std::vector<double>{  0.502494,  0.900855, -0.683727 } );

        Matrix<double> b2 = Matrix<double>( 1, 1 );
        b2.setColumn( 1, std::vector<double>{ -0.122890 } );

        layer1->weight = W1;
        layer1->bias = b1;

        layer2->weight = W2;
        layer2->bias = b2;

        Matrix<double> input( 4, 2 );
        input.setColumn( 1, std::vector<double>{  1.62434536, -0.52817175,  0.86540763,  1.74481176 } );
        input.setColumn( 2, std::vector<double>{ -0.61175641, -1.07296862, -2.3015387,  -0.7612069  } );

        Matrix<double> A( 1, 2 );
        A.setRow( 1, std::vector<double>{ 0.17007265, 0.2524272 } );

        nn->feedForward( input );

        return abs(layer2->getOutput().getCell(1, 1) - 0.17007264) < 0.001 && abs(layer2->getOutput().getCell(1, 2) -0.2524279) < 0.001;
    }

    static bool sigmoidBackward()
    {
        Matrix<double> AL( 1, 2 );
        Matrix<double>  Z( 1, 2 );
        Matrix<double> result(1, 2);
        AL.setRow( 1, std::vector<double>{ -0.416757, -0.056266 } );
         Z.setRow( 1, std::vector<double>{ 0.041539, -1.117925 } );

        result = Neuron::sigmoidBackward( AL, Z );

        // cout << result << endl;

        return
            abs(result.getCell(1, 1) - -0.1041445) < 0.001 &&
            abs(result.getCell(1, 2) - -0.0104479) < 0.001;
    }

    static void backward()
    {
        Layer* layer = new Layer( 1, nullptr, Neuron::sigmoidBackward );
        Layer* prevLayer = new Layer( 3, nullptr, Neuron::reluBackward );

        Matrix<double> AL(1, 2);
        Matrix<double> A_prev( 3, 2 );
        Matrix<double> W( 1, 3 );
        Matrix<double> b( 1, 1 );
        Matrix<double> Z( 1, 2 );

        AL.setRow( 1, std::vector<double>{ -0.416757, -0.056266 } );

        A_prev.setColumn( 1, std::vector<double>{ -2.136196,  1.793435,  0.502881 } );
        A_prev.setColumn( 2, std::vector<double>{  1.640270, -0.841747, -1.245288 } );

        W.setRow( 1, std::vector<double>{ -1.057952, -0.909007, 0.551454} );

        b.setColumn( 1, std::vector<double>{ 2.292208 } );

        Z.setRow( 1, std::vector<double>{ 0.0415399, -1.117925 } );

        prevLayer->output = A_prev;
        layer->dA     = AL;
        layer->Z      = Z;
        layer->weight = W;
        layer->bias   = b; // won't be used

        layer->backward( prevLayer );

        // TODO: finish comparation
        return;
    }

    static void model_backward()
    {
        Layer* layer0 = new Layer( 3, Neuron::dummy, nullptr, "inputLayer" );
        Layer* layer1 = new Layer( 3, Neuron::relu, Neuron::reluBackward, "hiddenLayer" );
        Layer* layer2 = new Layer( 1, Neuron::sigmoid, Neuron::sigmoidBackward, "ouputLayer" );

        NeuralNetwork* nn = new NeuralNetwork();
        nn->addLayer( layer0 );
        nn->addLayer( layer1 );
        nn->addLayer( layer2 );

        Matrix<double> A2( 1, 2 );
        A2.setRow( 1, std::vector<double>{ 1.78862847, 0.43650985 } );

        Matrix<double> Y( 1, 2 );
        Y.setRow( 1, std::vector<double>{ 1, 0 } );

        Matrix<double> Z2(1, 2);
        Z2.setRow( 1, std::vector<double>{ 0.64667545, -0.35627076 } );

        Matrix<double> W2( 1, 3 );
        W2.setRow( 1, std::vector<double>{ -1.02387576,  1.12397796, -0.13191423 } );

        Matrix<double> b2( 1, 1 );
        b2.setCell( 1, 1, -1.62328545 );

        Matrix<double> Z1( 3, 2 );
        Z1.setColumn( 1, std::vector<double>{ -0.7129932, -0.16051336, -0.23003072 } );
        Z1.setColumn( 2, std::vector<double>{  0.62524497, -0.76883635, 0.74505627 } );

        Matrix<double> A1( 3, 2 );
        A1.setColumn( 1, std::vector<double>{  1.97611078, -0.62641691, -2.41908317 } );
        A1.setColumn( 2, std::vector<double>{ -1.24412333, -0.80376609, -0.92379202 } );

        Matrix<double> W1( 3, 4 );
        W1.setRow( 1, std::vector<double>{ -1.31386475,  0.88462238,  0.88131804,  1.70957306 } );
        W1.setRow( 2, std::vector<double>{  0.05003364, -0.40467741, -0.54535995, -1.54647732 } );
        W1.setRow( 3, std::vector<double>{  0.98236743, -1.10106763, -1.18504653, -0.2056499  } );

        Matrix<double> b1( 3, 1 );
        b1.setColumn( 1, std::vector<double>{ 1.48614836, 0.23671627, -1.02378514 } );

        Matrix<double> A0( 4, 2 ); // X as original input of the network
        A0.setColumn( 1, std::vector<double>{  0.09649747, -0.2773882, -0.08274148, -0.04381817 } );
        A0.setColumn( 2, std::vector<double>{ -1.8634927, -0.35475898, -0.62700068, -0.47721803 } );


        layer2->output = A2;
        layer2->Z      = Z2;
        layer2->weight = W2;
        layer2->bias   = b2;

        layer1->output = A1;
        layer1->Z      = Z1;
        layer1->weight = W1;
        layer1->bias   = b1;

        layer0->output = A0;        // same as X, the input
        layer0->Z      = A0;        // same as A0 as this layer is just a pass through so edu purposes
        layer0->weight = Matrix<double>();
        layer0->bias   = Matrix<double>();

        nn->backPropagate( Y );

        cout << "Layer 2 (output):" << endl
             << layer2->dWeight << endl
             << layer2->dBias << endl;

        cout << "Layer 1 (hidden):" << endl
             << layer1->dWeight << endl
             << layer1->dBias << endl;

        // TODO: finish comparation
        return;
    }
};

void run_tests()
{
    cout << "Test model_forward: "    << ( Test::model_forward()   ? "pass" : "fail" ) << endl;
    cout << "Test sigmoid_backward: " << ( Test::sigmoidBackward() ? "pass" : "fail" ) << endl;

    Test::backward();
    Test::model_backward();

return;
}
