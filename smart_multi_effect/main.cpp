#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <unistd.h>

#include <iostream>

#include "EffectController/effectcontroller.h"
#include "SoundProcessing/soundcard.h"

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
#define BUTTON1 5
#define BUTTON2 6
#define BUTTON3 13
#define BUTTON4 19
#define BUTTON5 26

#include <thread>

#include <unistd.h>
#include <fcntl.h>
#include <qdebug.h>

int main(int argc, char *argv[])
{
#define N 1024

    SoundCard s(QAudioFormat::Endian::LittleEndian, 2, "", 44100,
                sizeof (int16_t) * 8, QAudioFormat::SampleType::SignedInt, N);
    sleep(1);
    s.SetOnBufferFill([](int16_t* buffer, size_t bufferSize){
        //fft
        std::cout << "read: " << bufferSize << "[\n  ";
        for(size_t i = 0; i < bufferSize; i += 128) {
            std::cout << buffer[i] << ", \n  ";
        }
        std::cout << "]" << std::endl;
        std::cout << std::endl;
        sleep(2);
    },1024/2);

    s.Start();

    double count = 0;
    while(true) {
        sleep(1);
        count += 1;
        std::cout << count <<  " sec" << std::endl;
    }

#if 0
    EffectController controller(INC_PIN, UD_PIN);

    controller.AddButton("button1", BUTTON1);
    controller.AddButton("button2", BUTTON2);
    controller.AddButton("button3", BUTTON3);
    controller.AddButton("button4", BUTTON4);
    controller.AddButton("button5", BUTTON5);

    controller.AddButtonEvent("button3", [&](EffectController* controller){
        static bool state = false;
        state = !state;
        state ? controller->GetEffect("over drive")->On() : controller->GetEffect("over drive")->Off();
    });
    controller.AddButtonEvent("button1", [&](EffectController* controller){
        static bool state = false;
        state = !state;
        state ? controller->GetEffect("delay")->On() : controller->GetEffect("delay")->Off();
    });
    controller.AddButtonEvent("button2", [&](EffectController* controller){
        static bool state = false;
        state = !state;
        state ? controller->GetEffect("tremolo")->On() : controller->GetEffect("tremolo")->Off();
    });

    std::thread t1([&](){
        while(true) {
            controller.UpdateButtons();
            usleep(10000);
        }
    });

    Effect e1(RELAY_1,
              Effect::EffectType::delay,
              Effect::EffectControlLayoutEllements::Speed | Effect::EffectControlLayoutEllements::Volume);
    e1.SetPotentiometer(Effect::EffectControlLayoutEllements::Speed, P1_PIN);
    e1.SetPotentiometer(Effect::EffectControlLayoutEllements::Volume, P2_PIN);
    controller.AddEffect("delay", &e1);

    Effect e2(RELAY_2,
              Effect::EffectType::tremolo,
              Effect::EffectControlLayoutEllements::Speed);
    e2.SetPotentiometer(Effect::EffectControlLayoutEllements::Speed, P3_PIN);
    controller.AddEffect("tremolo", &e2);

    Effect e3(RELAY_3,
              Effect::EffectType::delay,
              Effect::EffectControlLayoutEllements::Gain | Effect::EffectControlLayoutEllements::Volume);
    e3.SetPotentiometer(Effect::EffectControlLayoutEllements::Volume, P4_PIN);
    e3.SetPotentiometer(Effect::EffectControlLayoutEllements::Gain, P5_PIN);
    controller.AddEffect("over drive", &e3);

    //-----------

    controller.GetEffect("over drive")->Off();
    controller.GetEffect("tremolo")->Off();
    controller.GetEffect("delay")->Off();

    controller.SetAllToValue_Long();


    controller.GetEffect("over drive")->GetPotentiometer(Effect::EffectControlLayoutEllements::Gain)->SetTarget(0);
    controller.GetEffect("over drive")->GetPotentiometer(Effect::EffectControlLayoutEllements::Volume)->SetTarget(100);

    controller.GetEffect("tremolo")->GetPotentiometer(Effect::EffectControlLayoutEllements::Speed)->SetTarget(0);

    controller.GetEffect("delay")->GetPotentiometer(Effect::EffectControlLayoutEllements::Volume)->SetTarget(100);
    controller.GetEffect("delay")->GetPotentiometer(Effect::EffectControlLayoutEllements::Speed)->SetTarget(0);


    controller.SetAllToValue();




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

    t1.join();
#endif
#if 0
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
#endif

}
