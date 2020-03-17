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

    void SaveAll();
    bool LoadAll();

    std::map<QString, std::vector<QString>> GenPresetsMap();

    void AddPresetWindow(PresetWindow* presetWindow);

    PresetWindow* getCurrentPreset();

    hardware_ctrl::Preset* getPreset(QString set, QString name);

private:
    QQuickItem* window = nullptr;
    std::vector<PresetWindow*> presetWindows;
    QVariantMap presetsPath;
    int index = 0;

    std::map<QString, std::vector<QString>> presetsMap;

    QQmlApplicationEngine *engine;
    QQuickItem *parent;
};

#endif // PRESETSWINDOW_H
