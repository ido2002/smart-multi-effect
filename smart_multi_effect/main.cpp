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

const QUrl url(QStringLiteral("qrc:/main.qml"));

using namespace QtCharts;
using namespace CONF;
using namespace SOUND_PROCCESSING;
using namespace SOUND_CARD;

typedef Stroke::Note Note;

void recNote(std::string note, SoundProcessor& sp)
{
    std::list<Note> notes;
    notes.clear();
    if(note != "silence") {
        notes.push_back(Stroke::StringToNote(note));
    }

    std::cout << "\n---------------\n" << std::endl;
    usleep(200*1000);
    std::cout << "play: " << note << std::endl;
    usleep(750*1000);
    std::cout << "3" << std::endl;
    usleep(200*1000);
    std::cout << "2" << std::endl;
    usleep(200*1000);
    std::cout << "1" << std::endl;
    usleep(200*1000);
    std::cout << "listening..." << std::endl;
    sp.RecordSample(notes);
    usleep(50*1000);
    sp.RecordSample(notes);
    usleep(50*1000);
    sp.RecordSample(notes);
    usleep(50*1000);
    sp.RecordSample(notes);
    std::cout << "captured 4 snapshots!" << std::endl;
    usleep(100*1000);
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


#if 1
    SoundProcessor soundProccessor;
    soundProccessor.Start();

#if 1

    std::list<Note> AllNotes;
    for(Note n = Note::E0; n <= Note::E4; n = static_cast<Note>(n + 1)) {
        //AllNotes.push_back(n);
    }

    AllNotes.push_back(Note::C1);
    AllNotes.push_back(Note::D1);
    AllNotes.push_back(Note::E1);
    AllNotes.push_back(Note::F1);
    AllNotes.push_back(Note::G1);
    AllNotes.push_back(Note::A2);
    AllNotes.push_back(Note::B2);
    AllNotes.push_back(Note::C2);
    AllNotes.push_back(Note::D2);
    AllNotes.push_back(Note::E2);
    AllNotes.push_back(Note::F2);
    AllNotes.push_back(Note::G2);

    for(Note n : AllNotes) {
        recNote(Stroke::NoteToString(n), soundProccessor);
    }

    std::cout << "proccessing" << std::endl;

    soundProccessor.Learn();

    std::cout << "done" << std::endl;

#endif

    QXYSeries* series = new QSplineSeries();
    series->clear();
    series->append(0, 0);
    series->append(POSSIBLE_NOTES_COUNT, 1);

    QChartView* chartView = new QChartView();
    chartView->chart()->addSeries(series);
    chartView->chart()->createDefaultAxes();
    chartView->show();

    soundProccessor.AddFunctionOnBufferFill(
        [&](std::vector<float>, std::vector<float> notes) {
            series->clear();
            for(size_t i = 0; i <  POSSIBLE_NOTES_COUNT; i++) {
                series->append(i, notes[i]);
            }
            usleep(1000);
        });



#endif
    return app.exec();

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
