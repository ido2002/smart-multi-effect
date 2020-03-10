#include <QApplication>
#include "smartmultieffect.h"

int main(int argc, char *argv[])
{
    //start the application
    QApplication app(argc, argv);

    SmartMultiEffect smartMultiEffect;
    smartMultiEffect.Run();

    return app.exec();
}

