#ifndef NEURALNETWORK_H
#define NEURALNETWORK_H

#include <vector>
#include <list>
#include <map>
#include <QString>
#include <QVariantMap>

namespace sound_processing {

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

            void MapToLayer(QVariantMap map);
            QVariantMap LayerToMap();

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

            void LoadFromFile(QString path);
            void SaveToFile(QString path);

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

        void SaveToJson(QString path);

        void LoadFromJson(QString path);

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
        void SaveData(std::string path);

        void SaveNetwork(QString path) { m_net.SaveToFile(path); }
        void LoadNetwork(QString path) { m_net.LoadFromFile(path); }

        void ClearData();
        void ClearData(std::string category);

    private:
        neural_network_tools::Network m_net;
        std::map<std::string, std::list<NetworkDataSet>> m_datasetMap;
        float m_learningRate = 0.03f;
    };
}
#endif // NEURALNETWORK_H
