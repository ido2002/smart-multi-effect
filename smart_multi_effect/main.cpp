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

void recNote(vector<string> _notes, SoundProcessor& sp)
{
    std::vector<Note> notes;
    notes.clear();
    for(auto note : _notes) {
        notes.push_back(Stroke::StringToNote(note));
    }

    std::cout << "\n---------------\n" << std::endl;
    std::cout << "play: ";
    for(auto note : _notes) {
        std::cout << note << " ";
    }
    std::cout << " hard" << std::endl;
    std::cout << "Press Enter to Continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    usleep(1000*1000);
    std::cout << "3" << std::endl;
    usleep(500*1000);
    std::cout << "2" << std::endl;
    usleep(500*1000);
    std::cout << "1" << std::endl;
    usleep(500*1000);
    std::cout << "listening..." << std::endl;
    sp.RecordSample(notes);
    usleep(150*1000);
    sp.RecordSample(notes);
    usleep(150*1000);
    sp.RecordSample(notes);
    usleep(150*1000);
    sp.RecordSample(notes);
    std::cout << "captured 4 snapshots!" << std::endl;
    usleep(300*1000);
    std::cout << "..." << std::endl;
#if 1 // second time
    usleep(750*1000);std::cout << "play: ";
    for(auto note : _notes) {
        std::cout << note << " ";
    }
    std::cout << " soft" << std::endl;
    std::cout << "Press Enter to Continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    usleep(1000*1000);
    std::cout << "3" << std::endl;
    usleep(500*1000);
    std::cout << "2" << std::endl;
    usleep(500*1000);
    std::cout << "1" << std::endl;
    usleep(500*1000);
    std::cout << "listening..." << std::endl;
    sp.RecordSample(notes);
    usleep(150*1000);
    sp.RecordSample(notes);
    usleep(150*1000);
    sp.RecordSample(notes);
    usleep(150*1000);
    sp.RecordSample(notes);
    std::cout << "captured 4 snapshots!" << std::endl;
    usleep(300*1000);
    std::cout << "..." << std::endl;
    usleep(750*1000);
#endif
}

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

#if 1  //record

    //std::cout << "loading data..." << std::endl;
    //timerFunc([&](){ soundProccessor.Load(true, false); });

    soundProccessor.Start();
    std::list<Note> AllNotes;
    for(Note n = Note::E0; n <= Note::G0/*E4*/; n = static_cast<Note>(n + 1)) {
        AllNotes.push_back(n);
    }
//    recNote({ "E0", "A1", "D1", "G1", "B2", "E2" }, soundProccessor); //open
//    recNote({ "E0", "B1", "E1", "G1", "B2", "E2" }, soundProccessor); //Em
//    recNote({       "A1", "E1", "A1", "C2", "E2" }, soundProccessor); //Am
//    recNote({       "C1", "E1", "G1", "C2", "E2" }, soundProccessor); //C
    for(Note n : AllNotes) {
        soundProccessor.RecordSample({n});
        sleep(2);
    }

    //std::cout << "saving data..." << std::endl;
    //soundProccessor.Save(true, false);
    //std::cout << "done!" << std::endl;
#else
    std::cout << "loading data..." << std::endl;
    timerFunc([&](){ soundProccessor.Load(true, false); });

#endif

#if 0 //load network
    std::cout << "loading network..." << std::endl;
    timerFunc([&](){ soundProccessor.Load(false, true); });
#endif

#if 1  //learn
    soundProccessor.Stop();
    std::cout << "proccessing" << std::endl;
    float time_past = 0;
    int times = 2;
    for(int i = 1; i <= times; i++) {
        std::cout << "\n\n\n-- " << i << " --\n" << std::endl;
        time_past += timerFunc([&](){ soundProccessor.Learn(20); });
        //std::cout << "learned! saving network..." << std::endl;
        //time_past += timerFunc([&](){ soundProccessor.Save(false, true); });
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
        [&](std::vector<float>, std::vector<float> notes, float) {
            strongNotes.clear();
            series->clear();
            for(size_t i = 0; i < POSSIBLE_NOTES_COUNT; i++) {
                series->append(i, notes[i]);
                if(notes[i] > 0.25f) {
                    if(notes[i] > 0.85) {
                        strongNotes.push_back((Note)i);
                        cout << Stroke::NoteToString((Note)i) << " ";
                    }
                    else {
                        for(Note note : PstrongNotes) {
                            if((Note)i == note) {
                                strongNotes.push_back((Note)i);
                                cout << Stroke::NoteToString((Note)i) << " ";
                            }
                        }
                    }
                }
            }
            if(strongNotes.size() > 0)
                cout << endl;
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
