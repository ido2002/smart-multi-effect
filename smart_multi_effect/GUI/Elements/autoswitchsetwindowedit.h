#ifndef AUTOSWITCHSETWINDOWEDIT_H
#define AUTOSWITCHSETWINDOWEDIT_H

#include <QQuickItem>
#include <QQmlApplicationEngine>
#include <map>

#include "SoundProcessing/soundprocessor.h"
#include "EffectController/effectcontroller.h"
#include "presetswindow.h"

struct PlayStyleEdit
{
    PlayStyleEdit(QString name, QQuickItem* item);

    PlayStyleEdit(QVariantMap map, QQuickItem* item);

    QVariantMap GenMap();

    void UpdatePresets(PresetsWindow* presets);
    double Update(sound_processing::SoundProcessor* soundProcessor);
    double getThreshold();

    void Activate(hardware_ctrl::EffectController* controller, PresetsWindow* presets);
    void Disable();

    QString name;
    QString currentSetName = "";
    QString currentPresetName = "";

    QQuickItem* item = nullptr;
    QQuickItem* background = nullptr;

    QQuickItem* comboBox_set = nullptr;
    QQuickItem* comboBox_preset= nullptr;

    QQuickItem* slider_bassFreq = nullptr;
    QQuickItem* slider_highFreq = nullptr;

    QQuickItem* slider_bassFactor = nullptr;
    QQuickItem* slider_highFactor = nullptr;

    QQuickItem* dial_bassTarget = nullptr;
    QQuickItem* dial_highTarget = nullptr;

    QQuickItem* slider_threshold = nullptr;
    QQuickItem* progressBar_threshold = nullptr;

    std::vector<std::pair<QString, std::vector<QString>>> presets;
};

class AutoSwitchSetWindowEdit
{
public:
    AutoSwitchSetWindowEdit(QString name, QQmlApplicationEngine* engine, QQuickItem* parent);
    AutoSwitchSetWindowEdit(QVariantMap map, QQmlApplicationEngine* engine, QQuickItem* parent);

    QVariantMap GenMap();

    void Update(hardware_ctrl::EffectController* controller, sound_processing::SoundProcessor* soundProcessor, PresetsWindow* presets);
    void UpdatePresets(PresetsWindow* presets);

    void Show();
    void Hide();

    void activate_1(hardware_ctrl::EffectController *controller, PresetsWindow* presets);
    void activate_2(hardware_ctrl::EffectController *controller, PresetsWindow* presets);
    void activate_3(hardware_ctrl::EffectController *controller, PresetsWindow* presets);
    void autoMod(bool on);

    QString getName() { return name; }
    QString getName_1() { return playStyleEdit_1->name; }
    QString getName_2() { return playStyleEdit_2->name; }
    QString getName_3() { return playStyleEdit_3->name; }
private:
    QString name;

    bool autoModState = false;

    QQuickItem* window = nullptr;
    PlayStyleEdit* playStyleEdit_1 = nullptr;
    PlayStyleEdit* playStyleEdit_2 = nullptr;
    PlayStyleEdit* playStyleEdit_3 = nullptr;
    QQuickItem* headline = nullptr;
};

#endif // AUTOSWITCHSETWINDOWEDIT_H
