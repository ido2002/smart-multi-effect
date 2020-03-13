#ifndef PRESETSWINDOW_H
#define PRESETSWINDOW_H

#include <QQuickItem>
#include <QQmlApplicationEngine>
#include "presetwindow.h"
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

    void AddPresetWindow(PresetWindow* presetWindow);

    PresetWindow* getCurrentPreset();

private:
    QQuickItem* window = nullptr;
    std::vector<PresetWindow*> presetWindows;
    int index = 0;
};

#endif // PRESETSWINDOW_H
