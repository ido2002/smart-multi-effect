#ifndef RECORDNOTE_H
#define RECORDNOTE_H

#include <QQuickItem>
#include <QQmlApplicationEngine>
#include "SoundProcessing/soundprocessor.h"
#include <vector>
#include <thread>

class RecordNotePage
{
public:
    RecordNotePage(QQmlApplicationEngine *engine, QQuickItem *parent);

    void Show();
    void Hide();

    void update();
    void UpdateList();

    void up();
    void add();
    void remove();
    void record(sound_processing::SoundProcessor* soundProcessor);

private:
    std::vector<sound_processing::Stroke::Note> notes;
    sound_processing::Stroke::Note currentNote = sound_processing::Stroke::Note::A;

    std::thread* recordingThread = nullptr;

    sound_processing::SoundProcessor* soundProcessor = nullptr;

    QQuickItem* window;
    QQuickItem* busyIndicator;
    QQuickItem* notesLable;
    QQuickItem* noteLable;
};

#endif // RECORDNOTE_H
