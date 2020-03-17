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

    void UpdateIndex();

    void AddSet(AutoSwitchSetWindowEdit* set);

    AutoSwitchSetWindowEdit* getCurrentSet();

private:
    QQuickItem* window = nullptr;
    std::vector<AutoSwitchSetWindowEdit*> sets;
    int index = 0;
};

#endif // AUTOSWITCHSETSWINDOW_H
