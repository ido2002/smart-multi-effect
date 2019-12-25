#ifndef NEURALNETWORK_H
#define NEURALNETWORK_H

#include <vector>

namespace neural_network {
using namespace std;

struct node
{
    float value;
    vector< pair<node*, float/*weight*/> > connections;
};

struct layer
{
    vector<node*> nodes;
};

struct net
{
    vector<float> inputLayer;
};

}

#endif // NEURALNETWORK_H
