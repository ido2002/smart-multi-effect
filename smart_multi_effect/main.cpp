#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "SoundProcessing/soundprocessor.h"
#include <iostream>
#include <unistd.h>

int main(int argc, char *argv[])
{
#if 1
    SoundProcessor soundProccessor;
    soundProccessor.Start();


    sleep(1);
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

    std::cout << "run: " << std::endl;

    soundProccessor.AddFunctionOnBufferFill([](std::vector<float> fft, std::vector<float> notes){
        for(size_t i = 0; i < notes.size(); i++) {
            if(notes[i] > 0.5f) {
                std::cout << Stroke::NoteToString(static_cast<Stroke::Note>(i)) << std::endl;
            }
        }
        for(size_t i = 0; i < fft.size(); i++) {
            if(fft[i] > 0.2f) {
                std::cout << i << " : " << fft[i] << std::endl;
            }
        }
    });

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
