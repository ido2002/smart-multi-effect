#ifndef RECORDOCTAVE_H
#define RECORDOCTAVE_H

#include <QQuickItem>
#include <QQmlApplicationEngine>
#include "SoundProcessing/soundprocessor.h"
#include <vector>
#include <thread>

class RecordOctavePage
{
public:
    RecordOctavePage(QQmlApplicationEngine *engine, QQuickItem *parent);

    void Show();
    void Hide();

    void update();
    void UpdateList();

    void up();
    void add();
    void remove();
    void record(sound_processing::SoundProcessor* soundProcessor);

private:
    std::vector<sound_processing::Stroke::NoteOctave> octaves;
    sound_processing::Stroke::NoteOctave currentOctave = sound_processing::Stroke::NoteOctave::Low;

    std::thread* recordingThread = nullptr;
    std::vector<float>* octavesVector = nullptr;

    sound_processing::SoundProcessor* soundProcessor = nullptr;

    QQuickItem* window;
    QQuickItem* busyIndicator;
    QQuickItem* octavesLable;
    QQuickItem* octaveLable;
};

#endif // RECORDOCTAVE_H
