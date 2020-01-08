#include "neuralnetwork.h"
#include <cmath>
#include <ctime>
#include <QString>
#include <QDir>
#include <QUrl>
#include <QFile>
#include <QJsonObject>
#include <QVariant>
#include <QVariantMap>
#include <QVariantList>
#include "jsonreader.h"
#include <iostream>

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

void neural_network_tools::Network::LoadFromJson(QString path)
{
    QVariantMap map;
    if(!JsonReader::readJsonFile(path, map)) return;

    auto layer = map.find("layer").value().toList();
    this->layer.clear();
    this->layer.resize(layer.size());
    for(int i = 0; i < layer.size(); i++) {
        this->layer[i] = layer[i].toInt();
    }

    auto layers = map.find("layers").value().toList();
    this->layers.clear();
    this->layers.resize(layers.size());

    for(int i = 0; i < layers.size(); i++) {
        this->layers[i] = new Layer(this->layer[i], this->layer[i+1]);
        this->layers[i]->MapToLayer(layers[i].toMap());
    }
}

void neural_network_tools::Network::SaveToJson(QString path)
{
    QVariantMap map;

    QVariantList layer;
    for(size_t i = 0; i < this->layer.size(); i++) {
        layer.push_back((quint64)this->layer[i]);
    }
    map.insert("layer", layer);

    QVariantList layers;
    for(size_t i = 0; i < this->layers.size(); i++) {
        layers.push_back(this->layers[i]->LayerToMap());
    }
    map.insert("layers", layers);

    JsonReader::writeJsonFile(map, path);
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
        outputs[i] = biases[i]*0; // edit for bias
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

void neural_network_tools::Layer::MapToLayer(QVariantMap map)
{
    auto weights = map.find("weights").value().toList();
    this->weights.resize(weights.size());
    for(int i = 0; i < weights.size(); i++) {
        this->weights[i].resize(weights[i].toList().size());
        for(int j = 0; j < weights[i].toList().size(); j++) {
            this->weights[i][j] = weights[i].toList()[j].toFloat();
        }
    }

    auto biases = map.find("biases").value().toList();
    this->biases.resize(biases.size());
    for(int i = 0; i < biases.size(); i++) {
        this->biases[i] = biases[i].toFloat();
    }
}

QVariantMap neural_network_tools::Layer::LayerToMap()
{
    QVariantMap map;
    QVariantList biases;
    for(size_t i = 0; i < this->biases.size(); i++) {
        biases.push_back(this->biases[i]);
    }
    map.insert("biases", biases);

    QVariantList weights;
    for(size_t i = 0; i < this->weights.size(); i++) {
        QVariantList list;
        for(size_t j = 0; j < this->weights[i].size(); j++) {
            list.push_back(this->weights[i][j]);
        }
        weights.push_back(list);
    }
    map.insert("weights", weights);

    return map;
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
    for(size_t i = 1; i <= times; i++) {
        for(auto category : m_datasetMap) {
            for(auto dataset : category.second) {
                m_net.FeedForword(dataset.inputs);
                m_net.BackProp(dataset.expectedOutputs);
            }
        }
        if((i*100)%times == 0) {
            std::cout << (i*100)/times << "% learned[" << i << " / " << times << "]" << std::endl;
        }
    }
}

long long NeuralNetwork::LearnUntilWork(uint precisionPoint, size_t blocks, size_t limit)
{
    size_t block_count = blocks;
    for(size_t i = 0; i < limit; i++) {
        size_t count = 0;
        for(auto category : m_datasetMap) {
            for(auto dataset : category.second) {
                count++;
                m_net.FeedForword(dataset.inputs);
                m_net.BackProp(dataset.expectedOutputs);
            }
        }
        if(((i%blocks + 1)*100) % blocks == 0) {
            std::cout << ((i%blocks + 1)*100)/blocks << "% learned[" << i%blocks + 1 << " / " << blocks << "] total: " << i + 1 << std::endl;
        }
        block_count--;
        if(block_count == 0) {
            block_count = blocks;
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

void NeuralNetwork::LoadData(std::string path)
{
    QVariantMap map;
    QString _path;
    _path = QString::fromStdString(path) + "data.data";
    if(!JsonReader::readJsonFile(_path, map)) return;

    for(auto paths : map) {
        for (int i = 0; i < paths.toList().size(); i++) {
            NetworkDataSet data({}, {});
            data.LoadFromJson(paths.toList()[i].toString());
            this->AddData(paths.toList()[i].toString().toStdString(), data);
        }
    }
}

void NeuralNetwork::SaveData(std::string path)
{
    QVariantMap map;
    for(auto dataList : m_datasetMap) {
        QVariantList list;
        QString name = QString::fromStdString(dataList.first);
        size_t i = 0;
        for(auto data : dataList.second) {
            QString subName = name + "_" + QString::number(i);
            QString url = QString::fromStdString(path) + name + "/" + subName + ".data";
            data.SaveToJson(url);
            list.push_back(url);
            i++;
        }
        map.insert(name, list);
    }
    JsonReader::writeJsonFile(map, QString::fromStdString(path) + "data.data");
}

void NetworkDataSet::SaveToJson(QString path)
{
    QVariantMap map;
    QVariantList inputs;
    for(size_t i = 0; i < this->inputs.size(); i++) {
        inputs.push_back(this->inputs[i]);
    }
    map.insert("inputs", inputs);

    QVariantList expectedOutputs;
    for(size_t i = 0; i < this->expectedOutputs.size(); i++) {
        expectedOutputs.push_back(this->expectedOutputs[i]);
    }
    map.insert("expectedOutputs", expectedOutputs);

    JsonReader::writeJsonFile(map, path);
}

void NetworkDataSet::LoadFromJson(QString path)
{
    QVariantMap map;
    if(!JsonReader::readJsonFile(path, map)) return;

    auto inputs = map.find("inputs").value().toList();
    this->inputs.resize(inputs.size());
    for(int i = 0; i < inputs.size(); i++) {
        this->inputs[i] = inputs[i].toFloat();
    }

    auto expectedOutputs = map.find("expectedOutputs").value().toList();
    this->expectedOutputs.resize(expectedOutputs.size());
    for(int i = 0; i < expectedOutputs.size(); i++) {
        this->expectedOutputs[i] = expectedOutputs[i].toFloat();
    }
}
