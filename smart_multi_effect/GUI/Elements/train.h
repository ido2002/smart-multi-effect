#ifndef TRAIN_H
#define TRAIN_H

#include <QQuickItem>
#include <QQmlApplicationEngine>
#include "SoundProcessing/soundprocessor.h"
#include <thread>

class TrainingPage
{
public:
    TrainingPage(QQmlApplicationEngine *engine, QQuickItem *parent);

    void Show();
    void Hide();

    void update();
    void UpdateLabel();

    void up();
    void down();
    void learn(sound_processing::SoundProcessor* soundProcessor);
    void save(sound_processing::SoundProcessor* soundProcessor);

private:
    long repeats = 0;

    std::thread* learningThread = nullptr;

    sound_processing::SoundProcessor* soundProcessor = nullptr;

    QQuickItem* window;
    QQuickItem* busyIndicator;
    QQuickItem* repeatsLabel;
};

#endif // TRAIN_H
