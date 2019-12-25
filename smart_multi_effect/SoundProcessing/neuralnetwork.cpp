#include "neuralnetwork.h"
#include <cmath>
#include <ctime>

neural_network_tools::Network::Network(vector<std::size_t> layer) {
    this->layer.resize(layer.size());
    for(size_t i = 0; i < layer.size(); i++) {
        this->layer[i] = layer[i];
    }

    layers.resize(layer.size()-1);
    {
        size_t i = 0;
        for(auto& l : layers){
            l = new Layer(layer[i], layer[i+1]);
            i++;
        }
    }
}

void neural_network_tools::Network::Reset()
{
    for(auto it : layers) {
        it->InitializeWeights();
    }
}

std::vector<float> neural_network_tools::Network::FeedForword(vector<float> inputs)
{
    layers[0]->FeedForword(inputs);

    for(size_t i = 1; i < layers.size(); i++) {
        layers[i]->FeedForword(layers[i-1]->outputs);
    }

    return layers[layers.size() - 1]->outputs;
}

void neural_network_tools::Network::BackProp(vector<float> expected)
{
    for(size_t i = layers.size(); i > 0; i--) {
        if(i == layers.size()) {
            layers[i-1]->BackPropOutput(expected);
        } else {
            layers[i-1]->BackPropHidden(layers[i]->gamma, layers[i]->weights);
        }
    }

    for(size_t i = 0; i < layers.size(); i++) {
        layers[i]->UpdateWeights();
    }
}

neural_network_tools::Layer::Layer(std::size_t numberOfInputs, std::size_t numberOfOutputs){
    this->numberOfInputs = numberOfInputs;
    this->numberOfOutputs = numberOfOutputs;

    inputs.resize(numberOfInputs);
    outputs.resize(numberOfOutputs);

    weights.resize(numberOfOutputs);
    for(auto& it : weights){
        it.resize(numberOfInputs);
        for(float& f : it) {
            f = 0;
        }
    }

    weightsDelta.resize(numberOfOutputs);
    for(auto& it : weightsDelta){
        it.resize(numberOfInputs);
        for(float& f : it) {
            f = 0;
        }
    }

    gamma.resize(numberOfOutputs);
    error.resize(numberOfOutputs);

    biases.resize(numberOfOutputs);

    InitializeWeights();
}

std::vector<float> neural_network_tools::Layer::FeedForword(vector<float> inputs)
{
    this->inputs = inputs;

    for(size_t i = 0; i < numberOfOutputs; i++) {
        outputs[i] = biases[i];
        for(size_t j = 0; j < numberOfInputs; j++){
            outputs[i] += inputs[j] * weights[i][j];
        }
        outputs[i] = std::tanh(outputs[i]);
    }

    return outputs;
}

void neural_network_tools::Layer::InitializeWeights()
{
    srand(static_cast<uint>(time(nullptr)));

    for(auto& it : weights) {
        for(auto& w : it) {
            w = (static_cast<float>(rand()) / RAND_MAX) - 0.5f;
        }
    }

    for(auto& bias : biases) {
        bias = (static_cast<float>(rand()) / RAND_MAX) - 0.5f;
    }
}

void neural_network_tools::Layer::UpdateWeights()
{
    for(size_t i = 0; i < numberOfOutputs; i++) {
        for(size_t j = 0; j < numberOfInputs; j++) {
            weights[i][j] -= weightsDelta[i][j] * learningRate;
        }
    }
}

float TanHDer(float value){
    return 1 - (value * value);
}

void neural_network_tools::Layer::BackPropOutput(vector<float> expected)
{
    for(size_t i = 0; i < numberOfOutputs; i++) {
        error[i] = outputs[i] - expected[i];
    }

    for(size_t i = 0; i < numberOfOutputs; i++) {
        gamma[i] = error[i] * TanHDer(outputs[i]);
    }

    for(size_t i = 0; i < numberOfOutputs; i++) {
        for(size_t j = 0; j < numberOfInputs; j++) {
            weightsDelta[i][j] = gamma[i] * inputs[j];
        }
        biases[i] -= gamma[i] * learningRate;
    }

}

void neural_network_tools::Layer::BackPropHidden(vector<float> gammaForward, vector<vector<float> > weightsforward)
{
    for(size_t i = 0; i < numberOfOutputs; i++) {
        gamma[i] = 0;
        for(size_t j = 0; j < gammaForward.size(); j++) {
            gamma[i] += gammaForward[j] * weightsforward[j][i];
        }
        gamma[i] *= TanHDer(outputs[i]);
    }

    for(size_t i = 0; i < numberOfOutputs; i++) {
        for(size_t j = 0; j < numberOfInputs; j++) {
            weightsDelta[i][j] = gamma[i] * inputs[j];
        }
        biases[i] -= gamma[i] * learningRate;
    }
}

// ------------------ NeuralNetworkManager ------------------

NeuralNetwork::NeuralNetwork(std::vector<size_t> layer) : m_net(layer)
{
    m_datasetMap.insert(std::pair<std::string, std::list<NetworkDataSet>>(
                            "other", std::list<NetworkDataSet>()));
}

std::vector<float> NeuralNetwork::FeedForword(std::vector<float> inputs)
{
    return m_net.FeedForword(inputs);
}

void NeuralNetwork::SetLearningRate(float learningRate)
{
    m_learningRate = learningRate;
}

void NeuralNetwork::ResetWeightsAndBiases()
{
    m_net.Reset();
}

void NeuralNetwork::Learn(size_t times)
{
    for(size_t i = 0; i < times; i++) {
        for(auto category : m_datasetMap) {
            for(auto dataset : category.second) {
                m_net.FeedForword(dataset.inputs);
                m_net.BackProp(dataset.expectedOutputs);
            }
        }
    }
}

long long NeuralNetwork::LearnUntilWork(uint precisionPoint, size_t limit)
{
    for(size_t i = 0; i < limit; i++) {
        size_t count = 0;
        for(auto category : m_datasetMap) {
            for(auto dataset : category.second) {
                count++;
                m_net.FeedForword(dataset.inputs);
                m_net.BackProp(dataset.expectedOutputs);
            }
        }
        for(auto category : m_datasetMap) {
            for(auto dataset : category.second) {
                auto result = m_net.FeedForword(dataset.inputs);
                bool good = true;
                for(size_t j = 0; j < result.size(); j++) {
                    if(std::abs(result[j] - dataset.expectedOutputs[j]) >
                            static_cast<float>(std::pow(0.1, precisionPoint))) {
                        good = false;
                        break;
                    }
                }
                if(good) {
                    count--;
                }
            }
        }
        if(count == 0) {
            return static_cast<long long>(i);
        }
    }
    return -1;
}

void NeuralNetwork::AddData(NetworkDataSet data)
{
    m_datasetMap["other"].push_back(data);
}

void NeuralNetwork::AddData(std::string category, NetworkDataSet data)
{
    if(m_datasetMap.find(category) == m_datasetMap.end()) {
        m_datasetMap.insert(std::pair<std::string, std::list<NetworkDataSet>>(
                                category, std::list<NetworkDataSet>()));
    }
    m_datasetMap[category].push_back(data);
}

void NeuralNetwork::ClearData()
{
    m_datasetMap.clear();
}

void NeuralNetwork::ClearData(std::string category)
{
    if(m_datasetMap.find(category) != m_datasetMap.end()) {
        m_datasetMap[category].clear();
    }
}
