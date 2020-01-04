#ifndef NEURALNETWORK_H
#define NEURALNETWORK_H

// todo: save weights(Gabi), load samples from file(Gabi)

#include <vector>
#include <list>
#include <map>

namespace neural_network_tools {
const float learningRate = 0.03f;

using namespace std;

class Layer
{
public:
    Layer(size_t numberOfInputs, size_t numberOfOutputs);

    vector<float> FeedForword(vector<float> inputs);

    void InitializeWeights();

    void UpdateWeights();

    void BackPropOutput(vector<float> expected);

    void BackPropHidden(vector<float> gammaForward, vector<vector<float>> weightsforward);

public:
    size_t numberOfInputs;
    size_t numberOfOutputs;

    vector<float> outputs;
    vector<float> inputs;
    vector<vector<float>> weights;
    vector<vector<float>> weightsDelta;
    vector<float> gamma;
    vector<float> error;
    vector<float> biases;
};

class Network
{
public:
    Network(vector<size_t> layer);

    void Reset();

    vector<float> FeedForword(vector<float> inputs);

    void BackProp(vector<float> expected);

private:
    vector<size_t> layer;
    vector<Layer*> layers;
};
}

struct NetworkDataSet
{
    NetworkDataSet(std::vector<float> inputs, std::vector<float> expectedOutputs) {
        this->inputs = inputs;
        this->expectedOutputs = expectedOutputs;
    }

    static NetworkDataSet ByIndex(std::vector<float> inputs,
                                  size_t expectedOutputIndex, size_t outputSize) {
        std::vector<float> expectedOutputs(outputSize);
        for(auto& it : expectedOutputs) {
            it = 0.0f;
        }
        expectedOutputs[expectedOutputIndex] = 1.0f;
        return NetworkDataSet(inputs, expectedOutputs);
    }

    std::vector<float> inputs;
    std::vector<float> expectedOutputs;
};

class NeuralNetwork
{
public:
    NeuralNetwork(std::vector<size_t> layer);

    std::vector<float> FeedForword(std::vector<float> inputs);

    void SetLearningRate(float learningRate);

    void ResetWeightsAndBiases();

    void Learn(size_t times);
    long long LearnUntilWork(uint precisionPoint = 2, size_t blocks = 100, size_t limit = 50000/*50k*/);

    void AddData(NetworkDataSet data);
    void AddData(std::string category, NetworkDataSet data);
    void LoadData(std::string path);

    void ClearData();
    void ClearData(std::string category);

private:
    neural_network_tools::Network m_net;
    std::map<std::string, std::list<NetworkDataSet>> m_datasetMap;
    float m_learningRate = 0.03f;
};

#endif // NEURALNETWORK_H
