#include <QApplication>
#include "smartmultieffect.h"

#include "tobinary.h"
#include <fstream>
#include <iostream>

int main(int argc, char *argv[])
{
//    using namespace sound_processing::neural_network_tools;
//    Network net({3, 6, 2});
//    net.SaveToFile("test.test");
//    Network net2({1, 1});
//    net2.LoadFromFile("test.test");

//    return 0;

    //start the application
    QApplication app(argc, argv);

    SmartMultiEffect smartMultiEffect;
    smartMultiEffect.Run();

    return app.exec();
}

