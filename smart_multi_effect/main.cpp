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

#include "conf.h"

#include <limits>

const QUrl url(QStringLiteral("qrc:/main.qml"));

using namespace QtCharts;
using namespace CONF;
using namespace SOUND_PROCCESSING;
using namespace SOUND_CARD;

using ms = std::chrono::duration<float, std::milli>;
using namespace std::chrono;

typedef Stroke::Note Note;

using namespace std;

float timerFunc(std::function<void()> func)
{
    auto temp = std::chrono::steady_clock::now();
    func();
    float deltaTime = std::chrono::duration_cast<ms>(std::chrono::steady_clock::now() - temp).count();
    std::cout << "done in " << deltaTime / 1000.0f << " seconds!" << std::endl;
    return deltaTime / 1000.f;
}

int main(int argc, char *argv[])
{
    //start the application
    QApplication app(argc, argv);

#if 0
    QQmlApplicationEngine engine;
    engine.load(url);

    //get main window
    qDebug() << engine.rootObjects()[0];
    QQuickItem* parent = engine.rootObjects()[0]->findChild<QQuickItem*>("myRect");

    //create component
    QQmlComponent comp(&engine, parent);
    comp.loadUrl(QUrl("qrc:/EffectEdit/EffectEdit.qml"));

    //add element
    QQuickItem *rect2Instance = qobject_cast<QQuickItem *>(comp.create());
    engine.setObjectOwnership(rect2Instance,QQmlEngine::JavaScriptOwnership);
    rect2Instance->setParentItem(parent);

    auto dial1 = rect2Instance->childItems()[0]->findChild<QQuickItem *>("dial1")->findChild<QQuickItem*>("dial");
    qDebug() << dial1->property("value");
    dial1->setProperty("value", 1);
    dial1->parentItem()->findChild<QQuickItem *>("TextLable")->setProperty("text", "triger");
#endif


#if 1  //sound card
    SoundProcessor soundProccessor;

#if 0  //record

    std::cout << "loading data..." << std::endl;
    timerFunc([&](){ soundProccessor.Load(true, false); });

    soundProccessor.Start();
    std::list<Note> AllNotes;
    for(Note n = Note::E0; n <= Note::D4/*E4*/; n = static_cast<Note>(n + 1)) {
        //AllNotes.push_back(n);
    }

    for(Note n : AllNotes) {
        soundProccessor.RecordSample({n});
        sleep(2);
    }

    soundProccessor.RecordSample({});

    std::cout << "saving data..." << std::endl;
    soundProccessor.Save(true, false);
    std::cout << "done!" << std::endl;
#else
    std::cout << "loading data..." << std::endl;
    timerFunc([&](){ soundProccessor.Load(true, false); });

#endif

#if 1 //load network
    std::cout << "loading network..." << std::endl;
    timerFunc([&](){ soundProccessor.Load(false, true); });
#endif

#if 1  //learn
    soundProccessor.Stop();
    std::cout << "proccessing" << std::endl;
    float time_past = 0;
    int times = 100;
    for(int i = 1; i <= times; i++) {
        std::cout << "\n\n\n-- " << i << " / " << times <<" --\n" << std::endl;
        time_past += timerFunc([&](){ soundProccessor.Learn(50); });
        std::cout << "learned! saving network..." << std::endl;
        time_past += timerFunc([&](){ soundProccessor.Save(false, true); });
        float avgTime = time_past / i;
        std::cout << "time past: " << time_past << " seconds!\n";
        std::cout << "remaining time: " << (times - i) * avgTime / 3600.0f << " hours!" << std::endl;
    }
    std::cout << "done!" << std::endl;
#endif
    soundProccessor.Start();

    QXYSeries* series = new QSplineSeries();
    series->clear();
    series->append(0, 0);
    series->append(POSSIBLE_NOTES_COUNT, 1);

    QChartView* chartView = new QChartView();
    chartView->chart()->addSeries(series);
    chartView->chart()->createDefaultAxes();
    chartView->show();

    list<Note> strongNotes;
    list<Note> PstrongNotes;


#if 0
    soundProccessor.AddFunctionOnBufferFill(
        [&](std::vector<float>, std::vector<float>, float volume) {
        std::cout << volume << std::endl;
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
