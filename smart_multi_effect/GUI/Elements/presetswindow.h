#ifndef PRESETSWINDOW_H
#define PRESETSWINDOW_H

#include <QQuickItem>
#include <QQmlApplicationEngine>
#include "presetframe.h"
#include <vector>

class PresetsWindow
{
public:
    PresetsWindow(QQmlApplicationEngine* engine, QQuickItem* parent);

    void Show();
    void Hide();

    void choose();
    void left();
    void right();

    void UpdateIndex();

    void AddFrame(PresetFrame* frame);

    PresetFrame* getCurrentPreset();

private:
    QQuickItem* window = nullptr;
    std::vector<PresetFrame*> frames;
    int index = 0;
};

#endif // PRESETSWINDOW_H
