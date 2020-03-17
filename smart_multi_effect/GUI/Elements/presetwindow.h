#ifndef PRESETFRAME_H
#define PRESETFRAME_H

#include <QQuickItem>
#include <QQmlApplicationEngine>
#include "EffectController/preset.h"
#include "EffectController/effectcontroller.h"
#include "effect_gui.h"
#include <vector>

class Preset
{
public:
    Preset(QString setName, QString name, hardware_ctrl::Preset* preset, QQmlApplicationEngine* engine, QQuickItem* parent);
    Preset(QString setName, QString name, QQmlApplicationEngine* engine, QQuickItem* parent);

    void Update();

    void Show();
    void Hide();

    void Save();

    QString GenFilePath();

    void Refresh();

    QString getName();

    hardware_ctrl::Preset* getPreset() { return preset; };

private:
    QString name;
    QString setName;
    hardware_ctrl::Preset* preset;
    QQuickItem* editWindow = nullptr;
    //QQuickItem* editTime = nullptr;
    //QQuickItem* editResolution = nullptr;

    std::vector<GUI_elements::Effect_gui*> effects;
};

class PresetWindow
{
public:
    PresetWindow(QString name);

    QString getName() { return name; }
    Preset* getP1() { return p1; }
    Preset* getP2() { return p2; }
    Preset* getP3() { return p3; }
    Preset* getP4() { return p4; }

    Preset* getActivePreset() { return activePreset; }
    void setActivePreset(Preset* p) { activePreset = p; }

    void ShowActivePreset();
    void Hide();

    void setP1(Preset* p) { if(p1) delete p1; p1 = p; }
    void setP2(Preset* p) { if(p2) delete p2; p2 = p; }
    void setP3(Preset* p) { if(p3) delete p3; p3 = p; }
    void setP4(Preset* p) { if(p4) delete p4; p4 = p; }

private:
    QString name;
    Preset* p1 = nullptr;
    Preset* p2 = nullptr;
    Preset* p3 = nullptr;
    Preset* p4 = nullptr;
    Preset* activePreset = nullptr;
};

#endif // PRESETFRAME_H
