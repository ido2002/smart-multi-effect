#include <QQmlApplicationEngine>
#include <QApplication>

#include <QQuickItem>
#include <QQmlComponent>
#include <QDial>
#include <QVariant>

#include "SoundProcessing/soundprocessor.h"
#include <iostream>
#include <unistd.h>

const QUrl url(QStringLiteral("qrc:/main.qml"));

int main(int argc, char *argv[])
{
#if 1
    //start the application
    QApplication app(argc, argv);
    QQmlApplicationEngine engine;
    engine.load(url);

    //get main window
    qDebug() << engine.rootObjects()[0];
    QQuickItem* parent = engine.rootObjects()[0]->findChild<QQuickItem*>("myRect");

    //create component
    QQmlComponent comp(&engine, parent);
    comp.loadUrl(QUrl("qrc:/EffectEdit/EffectEdit.qml"));

    //add element
    QQuickItem *rect1Instance = qobject_cast<QQuickItem *>(comp.create());
    engine.setObjectOwnership(rect1Instance,QQmlEngine::JavaScriptOwnership);
    rect1Instance->setParentItem(parent);


    //add element
    QQuickItem *rect2Instance = qobject_cast<QQuickItem *>(comp.create());
    engine.setObjectOwnership(rect2Instance,QQmlEngine::JavaScriptOwnership);
    rect2Instance->setParentItem(parent);
    rect2Instance->setX(500);

    auto dial1 = rect2Instance->childItems()[0]->findChild<QQuickItem *>("dial1")->findChild<QQuickItem*>("dial");
    auto dial2 = rect2Instance->childItems()[0]->findChild<QQuickItem *>("dial2")->findChild<QQuickItem*>("dial");
    auto dial3 = rect2Instance->childItems()[0]->findChild<QQuickItem *>("dial3")->findChild<QQuickItem*>("dial");
    qDebug() << dial1->property("value");
    dial1->setProperty("value", 1);
    dial1->parentItem()->findChild<QQuickItem *>("TextLable")->setProperty("text", "triger");

    //wait for aplication to close
//    return app.exec();
#endif
#if 1
    SoundProcessor soundProccessor;
    soundProccessor.Start();


    sleep(1);
#if 0
    std::string input;
    std::cout << "\n\n> ";
    std::cout.flush();
    std::cin >> input;
    std::list<Stroke::Note> notes;
    while(input != "done") {
        notes.clear();
        if(input == "s") {
            soundProccessor.RecordSample({});
        } else {
            notes.push_back(Stroke::StringToNote(input));
            while(std::cin.peek() == ' '){
                std::cin >> input;
                notes.push_back(Stroke::StringToNote(input));
            }

            soundProccessor.RecordSample(notes);

            for(auto note : notes) {
                std::cout << Stroke::NoteToString(note) << ", ";
            }
            std::cout << std::endl;
    }
        std::cout << "\n\n> ";
        std::cout.flush();
        std::cin >> input;
    }

    soundProccessor.Learn();

    sleep(3);
#endif
    std::cout << "run: " << std::endl;

    soundProccessor.AddFunctionOnBufferFill(
        [&](std::vector<float> fft, std::vector<float> notes) {
            for(size_t i = 0; i < notes.size(); i++) {
                if(notes[i] > 0.4f) {
                    //std::cout << Stroke::NoteToString(static_cast<Stroke::Note>(i)) << std::endl;
                }
            }
            float max = 0.0f;
            size_t maxIndex = 0;
            for(size_t i = 2; i < fft.size() / 2; i++) {
                if(fft[i] > max) {
                    maxIndex = i;
                    max = fft[i];
                }
            }
            if(max >= dial1->property("value").toFloat())
                std::cout << maxIndex << " : " << max << std::endl;
        });

    return app.exec();//---
    while(true) {
        sleep(1);
    }
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
