#define RASPBERRY_PI    1
#define USE_GUI         1
#define USE_SOUNDCARD   1
#define LOAD_NETWORK    1
#define LOAD_DATA       1
#define RECORD_DATA     1
#define LEARN           1
#define SAVE_NETWORK    1
#define SAVE_DATA       1
#define VOLUME_GUI      1
#define FFT_GUI         1
#define NOTES_GUI       1
#define OCTAVE_GUI      1

#include <QApplication>

#include <iostream>
#include <unistd.h>

#include "SoundProcessing/soundprocessor.h"
#include "EffectController/effectcontroller.h"
#include "GUI/Elements/guimanager.h"
#include "GUI/Elements/testgui.h"
#include "conf.h"


const QUrl url(QStringLiteral("qrc:/main.qml"));
using namespace CONF;
using namespace SOUND_PROCCESSING;
using namespace SOUND_CARD;
using namespace sound_processing;
using namespace hardware_ctrl;
using ms = std::chrono::duration<float, std::milli>;
using type_element = hardware_ctrl::Effect::EffectControlLayoutEllements;

std::thread* button_thraed = nullptr;
float timerFunc(std::function<void()> func);

void configButtons(hardware_ctrl::EffectController& controller)
{
    controller.AddButton("b1", HARDWARE::BUTTON1);
    controller.AddButton("b2", HARDWARE::BUTTON2);
    controller.AddButton("b3", HARDWARE::BUTTON3);
    controller.AddButton("b4", HARDWARE::BUTTON4);
    controller.AddButton("b5", HARDWARE::BUTTON5);

    controller.AddButtonEvent("b1",[](EffectController* controller){
        for(int i = 0; i <= 100; i++) {
            controller->GetEffect(NAMES::OVERDRIVE)->GetPotentiometer(type_element::Gain)->SetTarget(i);
            controller->GetEffect(NAMES::OVERDRIVE)->GetPotentiometer(type_element::Volume)->SetTarget(100 - i/5);
            controller->GetEffect(NAMES::OVERDRIVE)->GetPotentiometer(type_element::Tone)->SetTarget(80+ i/8);
            controller->GetEffect(NAMES::OVERDRIVE)->On();

            controller->GetEffect(NAMES::DELAY)->GetPotentiometer(type_element::Delay)->SetTarget(30);
            controller->GetEffect(NAMES::DELAY)->GetPotentiometer(type_element::Volume)->SetTarget(50 + i/4);
            controller->GetEffect(NAMES::DELAY)->On();

            controller->GetEffect(NAMES::TREMOLO)->GetPotentiometer(type_element::Speed)->SetTarget(10);
            controller->GetEffect(NAMES::TREMOLO)->Off();

            controller->SetAllToValue();
            usleep(1000 * 10);
        }
    });

    controller.AddButtonEvent("b2",[](EffectController* controller){
        controller->GetEffect(NAMES::OVERDRIVE)->GetPotentiometer(type_element::Gain)->SetTarget(0);
        controller->GetEffect(NAMES::OVERDRIVE)->GetPotentiometer(type_element::Volume)->SetTarget(100);
        controller->GetEffect(NAMES::OVERDRIVE)->GetPotentiometer(type_element::Tone)->SetTarget(80);
        controller->GetEffect(NAMES::OVERDRIVE)->On();

        controller->GetEffect(NAMES::DELAY)->GetPotentiometer(type_element::Delay)->SetTarget(30);
        controller->GetEffect(NAMES::DELAY)->GetPotentiometer(type_element::Volume)->SetTarget(50);
        controller->GetEffect(NAMES::DELAY)->On();

        controller->GetEffect(NAMES::TREMOLO)->GetPotentiometer(type_element::Speed)->SetTarget(10);
        controller->GetEffect(NAMES::TREMOLO)->Off();

        controller->SetAllToValue();
    });

    controller.AddButtonEvent("b3",[](EffectController* controller){
        controller->GetEffect(NAMES::OVERDRIVE)->GetPotentiometer(type_element::Gain)->SetTarget(100);
        controller->GetEffect(NAMES::OVERDRIVE)->GetPotentiometer(type_element::Volume)->SetTarget(70);
        controller->GetEffect(NAMES::OVERDRIVE)->GetPotentiometer(type_element::Tone)->SetTarget(75);
        controller->GetEffect(NAMES::OVERDRIVE)->Off();

        controller->GetEffect(NAMES::DELAY)->GetPotentiometer(type_element::Delay)->SetTarget(50);
        controller->GetEffect(NAMES::DELAY)->GetPotentiometer(type_element::Volume)->SetTarget(30);
        controller->GetEffect(NAMES::DELAY)->On();

        controller->GetEffect(NAMES::TREMOLO)->GetPotentiometer(type_element::Speed)->SetTarget(50);
        controller->GetEffect(NAMES::TREMOLO)->On();

        controller->SetAllToValue();
    });

    controller.AddButtonEvent("b4",[](EffectController* controller){
        controller->GetEffect(NAMES::OVERDRIVE)->GetPotentiometer(type_element::Gain)->SetTarget(100);
        controller->GetEffect(NAMES::OVERDRIVE)->GetPotentiometer(type_element::Volume)->SetTarget(70);
        controller->GetEffect(NAMES::OVERDRIVE)->GetPotentiometer(type_element::Tone)->SetTarget(75);
        controller->GetEffect(NAMES::OVERDRIVE)->Off();

        controller->GetEffect(NAMES::DELAY)->GetPotentiometer(type_element::Delay)->SetTarget(50);
        controller->GetEffect(NAMES::DELAY)->GetPotentiometer(type_element::Volume)->SetTarget(30);
        controller->GetEffect(NAMES::DELAY)->Off();

        controller->GetEffect(NAMES::TREMOLO)->GetPotentiometer(type_element::Speed)->SetTarget(10);
        controller->GetEffect(NAMES::TREMOLO)->Off();

        controller->SetAllToValue();
    });

    controller.AddButtonEvent("b5",[](EffectController* controller){
        controller->GetEffect(NAMES::OVERDRIVE)->GetPotentiometer(type_element::Gain)->SetTarget(100);
        controller->GetEffect(NAMES::OVERDRIVE)->GetPotentiometer(type_element::Volume)->SetTarget(70);
        controller->GetEffect(NAMES::OVERDRIVE)->GetPotentiometer(type_element::Tone)->SetTarget(100);
        controller->GetEffect(NAMES::OVERDRIVE)->On();

        controller->GetEffect(NAMES::DELAY)->GetPotentiometer(type_element::Delay)->SetTarget(25);
        controller->GetEffect(NAMES::DELAY)->GetPotentiometer(type_element::Volume)->SetTarget(10);
        controller->GetEffect(NAMES::DELAY)->On();

        controller->GetEffect(NAMES::TREMOLO)->GetPotentiometer(type_element::Speed)->SetTarget(100);
        controller->GetEffect(NAMES::TREMOLO)->Off();

        controller->SetAllToValue();
    });

    button_thraed = new std::thread([&]() {
        while(true) {
            controller.UpdateButtons();
        }
    });
}

int main(int argc, char *argv[])
{
    //start the application
    QApplication app(argc, argv);

#if RASPBERRY_PI
    hardware_ctrl::EffectController controller(HARDWARE::INC_PIN, HARDWARE::UD_PIN);
    controller.Initialize();
    controller.SetAllToValue_Long();
    configButtons(controller);
#endif


#if USE_GUI
    QQmlApplicationEngine engine;
    engine.load(url);

    //get main window
    qDebug() << engine.rootObjects()[0];
    QQuickItem* mainItem = engine.rootObjects()[0]->findChild<QQuickItem*>("myRect");

#if RASPBERRY_PI
    Effect* e1 = controller.GetEffect(NAMES::OVERDRIVE);
    GUI_elements::Effect_gui e1G(QString::fromStdString(NAMES::OVERDRIVE), mainItem, &engine, e1);
#endif

#endif


#if USE_SOUNDCARD
    SoundProcessor soundProccessor;


#if LOAD_DATA
    soundProccessor.getNoteRecognition().LoadNetworkDataSets();
#endif
#if LOAD_NETWORK
    soundProccessor.getNoteRecognition().LoadNetwork();
#endif


#if RECORD_DATA
    std::cout << "A..." << std::endl;
    soundProccessor.RecordNoteSample({Stroke::Note::A});
    std::cout << "A..." << std::endl;
    soundProccessor.RecordNoteSample({Stroke::Note::A});
    std::cout << "A..." << std::endl;
    soundProccessor.RecordNoteSample({Stroke::Note::A});

    std::cout << "D..." << std::endl;
    soundProccessor.RecordNoteSample({Stroke::Note::D});
    std::cout << "D..." << std::endl;
    soundProccessor.RecordNoteSample({Stroke::Note::D});
    std::cout << "D..." << std::endl;
    soundProccessor.RecordNoteSample({Stroke::Note::D});

    std::cout << "low..." << std::endl;
    soundProccessor.RecordOctaveSample({1.0f, 0.0f, 0.0f});
    std::cout << "low..." << std::endl;
    soundProccessor.RecordOctaveSample({1.0f, 0.0f, 0.0f});
    std::cout << "low..." << std::endl;
    soundProccessor.RecordOctaveSample({1.0f, 0.0f, 0.0f});

    std::cout << "mid..." << std::endl;
    soundProccessor.RecordOctaveSample({0.0f, 1.0f, 0.0f});
    std::cout << "mid..." << std::endl;
    soundProccessor.RecordOctaveSample({0.0f, 1.0f, 0.0f});
    std::cout << "mid..." << std::endl;
    soundProccessor.RecordOctaveSample({0.0f, 1.0f, 0.0f});

    std::cout << "high..." << std::endl;
    soundProccessor.RecordOctaveSample({0.0f, 0.0f, 1.0f});
    std::cout << "high..." << std::endl;
    soundProccessor.RecordOctaveSample({0.0f, 0.0f, 1.0f});
    std::cout << "high..." << std::endl;
    soundProccessor.RecordOctaveSample({0.0f, 0.0f, 1.0f});
#endif


#if LEARN
    soundProccessor.Learn();
#endif


#if SAVE_NETWORK
    soundProccessor.getNoteRecognition().SaveNetwork();
#endif
#if SAVE_DATA
    soundProccessor.getNoteRecognition().SaveNetworkDataSets();
#endif


#if VOLUME_GUI
    TestGui::show_volume_test(soundProccessor, 300, 500, 0, 1);
#endif
#if FFT_GUI
    TestGui::show_fft_test(soundProccessor, 600, 500, 0, 1, 8);
#endif
#if NOTES_GUI
    TestGui::show_notes_test(soundProccessor, 500, 500, 0, 1);
#endif
#if OCTAVE_GUI
    TestGui::show_octave_test(soundProccessor, 300, 500, 0, 1);
#endif


    soundProccessor.Start();
#endif

    return app.exec();
}

float timerFunc(std::function<void()> func)
{
    auto temp = std::chrono::steady_clock::now();
    func();
    float deltaTime = std::chrono::duration_cast<ms>(std::chrono::steady_clock::now() - temp).count();
    std::cout << "done in " << deltaTime / 1000.0f << " seconds!" << std::endl;
    return deltaTime / 1000.f;
}
