#ifndef AUTOSWITCHSETSWINDOW_H
#define AUTOSWITCHSETSWINDOW_H

#include <QQuickItem>
#include <QQmlApplicationEngine>
#include "autoswitchsetwindowedit.h"
#include <vector>

class AutoSwitchSetsWindow
{
public:
    AutoSwitchSetsWindow(QQmlApplicationEngine* engine, QQuickItem* parent);

    void UpdatePresets(PresetsWindow* presets);

    void Show();
    void Hide();

    void choose();
    void left();
    void right();

    void SaveAll();
    bool LoadAll();

    void UpdateIndex();

    void AddSet(AutoSwitchSetWindowEdit* set);

    AutoSwitchSetWindowEdit* getCurrentSet();

private:
    QQmlApplicationEngine* engine = nullptr;
    QQuickItem* parent = nullptr;
    QQuickItem* window = nullptr;
    std::vector<AutoSwitchSetWindowEdit*> sets;
    QVariantMap setsPath;
    int index = 0;
};

#endif // AUTOSWITCHSETSWINDOW_H
