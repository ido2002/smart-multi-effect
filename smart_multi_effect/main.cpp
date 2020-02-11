#define RASPBERRY_PI 1
#define USE_GUI 1
#define USE_SOUNDCARD 0
#define LOAD_NETWORK 0
#define LOAD_DATA 0
#define LEARN 0
#define RECORD_DATA 0


#include <QQmlApplicationEngine>
#include <QApplication>

#include <QQuickItem>
#include <QQmlComponent>
#include <QDial>
#include <QVariant>

#include <QChartView>
#include <QChart>
#include <QtCharts>
#include <QLineSeries>

#include "SoundProcessing/soundprocessor.h"
#include <iostream>
#include <unistd.h>


#include <limits>

#include "conf.h"
#include "EffectController/effect.h"
#include "EffectController/effectcontroller.h"

#include "GUI/Elements/effect_gui.h"

const QUrl url(QStringLiteral("qrc:/main.qml"));

using namespace QtCharts;
using namespace CONF;
using namespace SOUND_PROCCESSING;
using namespace SOUND_CARD;
using namespace sound_processing;
using namespace hardware_ctrl;

using ms = std::chrono::duration<float, std::milli>;
using namespace std::chrono;

using Note = Stroke::Note;

using namespace std;

using type_element = hardware_ctrl::Effect::EffectControlLayoutEllements;

float timerFunc(std::function<void()> func)
{
    auto temp = std::chrono::steady_clock::now();
    func();
    float deltaTime = std::chrono::duration_cast<ms>(std::chrono::steady_clock::now() - temp).count();
    std::cout << "done in " << deltaTime / 1000.0f << " seconds!" << std::endl;
    return deltaTime / 1000.f;
}

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

    std::thread t1([&]() {
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
    //controller.SetAllToValue_Long();
    //configButtons(controller);
#endif

#if USE_GUI
    QQmlApplicationEngine engine;
    engine.load(url);

    //get main window
    qDebug() << engine.rootObjects()[0];
    QQuickItem* parent = engine.rootObjects()[0]->findChild<QQuickItem*>("myRect");

    Effect* e1 = controller.GetEffect(NAMES::OVERDRIVE);

    GUI_elements::Effect_gui e1G(QString::fromStdString(NAMES::OVERDRIVE), parent, &engine, e1);

//    //create component
//    QQmlComponent comp(&engine, parent);
//    comp.loadUrl(QUrl("qrc:/EffectEdit/EffectEdit.qml"));

//    //add element
//    QQuickItem *rect2Instance = qobject_cast<QQuickItem *>(comp.create());
//    engine.setObjectOwnership(rect2Instance,QQmlEngine::JavaScriptOwnership);
//    rect2Instance->setParentItem(parent);

//    auto dial1 = rect2Instance->childItems()[0]->findChild<QQuickItem *>("dial1")->findChild<QQuickItem*>("dial");
//    qDebug() << dial1->property("value");
//    dial1->setProperty("value", 1);
//    dial1->parentItem()->findChild<QQuickItem *>("TextLable")->setProperty("text", "triger");
#endif


#if USE_SOUNDCARD
    SoundProcessor soundProccessor;

#if RECORD_DATA

    std::cout << "loading data..." << std::endl;
    timerFunc([&](){ soundProccessor.Load(true, false); });

    soundProccessor.Start();
    std::list<Note> AllNotes;
    for(Note n = Note::E0; n <= Note::E2/*E4*/; n = static_cast<Note>(n + 1)) {
        AllNotes.push_back(n);
    }

    sleep(3);
    for(Note n : AllNotes) {
        soundProccessor.RecordSample({n});
        sleep(1);
    }

    //soundProccessor.RecordSample({Note::E0, Note::G1, Note::B2, Note::E2});
    sleep(1);

    std::cout << "saving data..." << std::endl;
    soundProccessor.Save(true, false);
    std::cout << "done!" << std::endl;
#endif
#if LOAD_DATA
    std::cout << "loading data..." << std::endl;
    timerFunc([&](){ soundProccessor.Load(true, false); });

#endif

#if LOAD_NETWORK
    std::cout << "loading network..." << std::endl;
    timerFunc([&](){ soundProccessor.Load(false, true); });
#endif

#if LEARN
    soundProccessor.Stop();
    std::cout << "proccessing" << std::endl;
    float time_past = 0;
    int times = 10;
    for(int i = 1; i <= times; i++) {
        std::cout << "\n\n\n-- " << i << " / " << times <<" --\n" << std::endl;
        time_past += timerFunc([&](){ soundProccessor.Learn(1000); });
        std::cout << "learned! saving network..." << std::endl;
        time_past += timerFunc([&](){ soundProccessor.Save(false, true); });
        float avgTime = time_past / i;
        std::cout << "time past: " << time_past << " seconds!\n";
        std::cout << "remaining time: " << (times - i) * avgTime / 3600.0f << " hours!" << std::endl;
    }
    std::cout << "done!" << std::endl;
#endif

    QXYSeries* series = new QSplineSeries();
    series->clear();
    series->append(-5, 0);
    series->append(POSSIBLE_NOTES_COUNT + 5, 1);
    //series->append(FFT_COUNT/4, 1);

    QChartView* chartView = new QChartView();
    chartView->chart()->addSeries(series);
    chartView->chart()->createDefaultAxes();
    chartView->show();

    list<Note> strongNotes;
    list<Note> PstrongNotes;

    sleep(2);

    soundProccessor.Start();


#if 0
    soundProccessor.AddFunctionOnBufferFill(
        [&](std::vector<float> fft, std::vector<float>, float) {
        series->clear();
        for(size_t i = 0; i < fft.size(); i++) {
            series->append(i, fft[i]);
        }
    });
#endif

#if 1
    soundProccessor.AddFunctionOnBufferFill(
        [&](std::vector<float>, std::vector<float> notes, float volume) {
            strongNotes.clear();
            series->clear();
            for(size_t i = 0; i < POSSIBLE_NOTES_COUNT; i++) {
                series->append(i, notes[i]);
                if(notes[i] > 0.25f) {
                    if(notes[i] > 0.85) {
                        strongNotes.push_back((Note)i);
                        std::cout << Stroke::NoteToString((Note)i) << " ";
                    }
                    else {
                        for(Note note : PstrongNotes) {
                            if((Note)i == note) {
                                strongNotes.push_back((Note)i);
                                std::cout << Stroke::NoteToString((Note)i) << " ";
                            }
                        }
                    }
                }
            }
            if(strongNotes.size() > 0)
                std::cout << volume << std::endl;
            PstrongNotes.clear();
            for(Note note : strongNotes) {
                PstrongNotes.push_back(note);
            }
            usleep(1000);
        });
#endif

#endif

    return app.exec();
}
