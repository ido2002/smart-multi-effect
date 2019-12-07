#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <unistd.h>

#include "EffectController/effectcontroller.h"

#define INC_PIN 17
#define UD_PIN 27
#define P1_PIN 4
#define P2_PIN 23
#define P3_PIN 18
#define P4_PIN 12
#define P5_PIN 22
#define P6_PIN 24
#define RELAY_1 20
#define RELAY_2 21
#define RELAY_3 16

#include <thread>

int main(int argc, char *argv[])
{


    EffectController controller(INC_PIN, UD_PIN);
    Effect e1(RELAY_1,
              Effect::delay,
              Effect::Speed | Effect::Volume);
    e1.SetPotentiometer(Effect::Speed, P1_PIN);
    e1.SetPotentiometer(Effect::Volume, P2_PIN);
    controller.AddEffect("delay", &e1);

    Effect e2(RELAY_2,
              Effect::tremolo,
              Effect::Speed);
    e2.SetPotentiometer(Effect::Speed, P3_PIN);
    controller.AddEffect("tremolo", &e2);

    Effect e3(RELAY_3,
              Effect::delay,
              Effect::Gain | Effect::Volume);
    e3.SetPotentiometer(Effect::Volume, P4_PIN);
    e3.SetPotentiometer(Effect::Gain, P5_PIN);
    controller.AddEffect("over drive", &e3);

    //-----------

    controller.SetAllToValue_Long();


    controller.GetEffect("over drive")->GetPotentiometer(Effect::Gain)->SetTarget(0);
    controller.GetEffect("over drive")->GetPotentiometer(Effect::Volume)->SetTarget(100);

    controller.GetEffect("tremolo")->GetPotentiometer(Effect::Speed)->SetTarget(0);

    controller.GetEffect("delay")->GetPotentiometer(Effect::Volume)->SetTarget(100);
    controller.GetEffect("delay")->GetPotentiometer(Effect::Speed)->SetTarget(0);


    controller.SetAllToValue();


    controller.GetEffect("over drive")->Off();
    controller.GetEffect("tremolo")->Off();
    controller.GetEffect("delay")->Off();


    for(int i = 0; i < 2; i++) {
        for(uint j = 0; j <= 100; j += 1) {
            usleep(10000);

            controller.GetEffect("over drive")->GetPotentiometer(Effect::Gain)->SetTarget(j);
            controller.GetEffect("over drive")->GetPotentiometer(Effect::Volume)->SetTarget(100-j);

            controller.GetEffect("tremolo")->GetPotentiometer(Effect::Speed)->SetTarget(j);

            controller.GetEffect("delay")->GetPotentiometer(Effect::Volume)->SetTarget(100-j);
            controller.GetEffect("delay")->GetPotentiometer(Effect::Speed)->SetTarget(j);

            controller.SetAllToValue();
        }
        for(uint j = 100; j > 0; j -= 1) {
            usleep(10000);

            controller.GetEffect("over drive")->GetPotentiometer(Effect::Gain)->SetTarget(j);
            controller.GetEffect("over drive")->GetPotentiometer(Effect::Volume)->SetTarget(100-j);

            controller.GetEffect("tremolo")->GetPotentiometer(Effect::Speed)->SetTarget(j);

            controller.GetEffect("delay")->GetPotentiometer(Effect::Volume)->SetTarget(100-j);
            controller.GetEffect("delay")->GetPotentiometer(Effect::Speed)->SetTarget(j);

            controller.SetAllToValue();
        }
    }

    controller.GetEffect("over drive")->On();
    controller.GetEffect("tremolo")->On();
    controller.GetEffect("delay")->On();

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
