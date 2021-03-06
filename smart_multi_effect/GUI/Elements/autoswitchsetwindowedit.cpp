#include "autoswitchsetwindowedit.h"
#include "conf.h"
#include <QStringList>

using namespace CONF::GUI_PARAMETERS;
using namespace GENERAL_GUI_PROPERTIES_NAMES;
using namespace SONG_EDIT_PAGE;
using namespace CONF::SOUND_PROCCESSING;
using namespace CONF::RIFF_RECOGNITION;
using namespace CONF::NOTE_RECOGNITION;

PlayStyleEdit::PlayStyleEdit(QString name, QQuickItem *item)
{
    this->item = item;
    this->name = name;

    background = item->findChild<QQuickItem*>(STYLE_BACKGROUND);

    comboBox_set = item->findChild<QQuickItem*>(STYLE_PRESET_SET_COMBO_BOX);
    comboBox_preset= item->findChild<QQuickItem*>(STYLE_PRESET_NAME_COMBO_BOX);

    slider_bassFreq = item->findChild<QQuickItem*>(STYLE_BASS_TOP_SLIDER);
    slider_highFreq = item->findChild<QQuickItem*>(STYLE_HIGH_BOTTOM_SLIDER);

    slider_bassFactor = item->findChild<QQuickItem*>(STYLE_BASS_FACTOR_SLIDER);
    slider_highFactor = item->findChild<QQuickItem*>(STYLE_HIGH_FACTOR_SLIDER);

    dial_bassTarget = item->findChild<QQuickItem*>(STYLE_BASS_TARGET_DIAL);
    dial_highTarget = item->findChild<QQuickItem*>(STYLE_HIGH_TARGET_DIAL);

    slider_threshold = item->findChild<QQuickItem*>(STYLE_THRESHOLD_SLIDER);
    progressBar_threshold = item->findChild<QQuickItem*>(STYLE_THRESHOLD_PROGRESS_BAR);
}

PlayStyleEdit::PlayStyleEdit(QVariantMap map, QQuickItem *item)
{
    this->item = item;

    background = item->findChild<QQuickItem*>(STYLE_BACKGROUND);

    comboBox_set = item->findChild<QQuickItem*>(STYLE_PRESET_SET_COMBO_BOX);
    comboBox_preset= item->findChild<QQuickItem*>(STYLE_PRESET_NAME_COMBO_BOX);

    slider_bassFreq = item->findChild<QQuickItem*>(STYLE_BASS_TOP_SLIDER);
    slider_highFreq = item->findChild<QQuickItem*>(STYLE_HIGH_BOTTOM_SLIDER);

    slider_bassFactor = item->findChild<QQuickItem*>(STYLE_BASS_FACTOR_SLIDER);
    slider_highFactor = item->findChild<QQuickItem*>(STYLE_HIGH_FACTOR_SLIDER);

    dial_bassTarget = item->findChild<QQuickItem*>(STYLE_BASS_TARGET_DIAL);
    dial_highTarget = item->findChild<QQuickItem*>(STYLE_HIGH_TARGET_DIAL);

    slider_threshold = item->findChild<QQuickItem*>(STYLE_THRESHOLD_SLIDER);
    progressBar_threshold = item->findChild<QQuickItem*>(STYLE_THRESHOLD_PROGRESS_BAR);

    this->name = map["name"].toString();
    this->currentSetName = map["set"].toString();
    this->currentPresetName = map["preset"].toString();

    comboBox_set->setProperty(COMBOBOX_VALUE, currentSetName);
    comboBox_preset->setProperty(COMBOBOX_VALUE, currentPresetName);


    slider_bassFreq->setProperty(SLIDER_VALUE, map["slider_bassFreq"].toDouble());
    slider_highFreq->setProperty(SLIDER_VALUE, map["slider_highFreq"].toDouble());

    slider_bassFactor->setProperty(SLIDER_VALUE, map["slider_bassFactor"].toDouble());
    slider_highFactor->setProperty(SLIDER_VALUE, map["slider_highFactor"].toDouble());

    dial_bassTarget->setProperty(DIAL_VALUE, map["dial_bassTarget"].toDouble());
    dial_highTarget->setProperty(DIAL_VALUE, map["dial_highTarget"].toDouble());

    slider_threshold->setProperty(SLIDER_VALUE, map["slider_threshold"].toDouble());
}

QVariantMap PlayStyleEdit::GenMap()
{
    QVariantMap map;

    map.insert("name", name);
    map.insert("set", currentSetName);
    map.insert("preset", currentPresetName);

    map.insert("slider_bassFreq", slider_bassFreq->property(SLIDER_VALUE).toDouble());
    map.insert("slider_highFreq", slider_highFreq->property(SLIDER_VALUE).toDouble());

    map.insert("slider_bassFactor", slider_bassFactor->property(SLIDER_VALUE).toDouble());
    map.insert("slider_highFactor", slider_highFactor->property(SLIDER_VALUE).toDouble());

    map.insert("dial_bassTarget", dial_bassTarget->property(DIAL_VALUE).toDouble());
    map.insert("dial_highTarget", dial_highTarget->property(DIAL_VALUE).toDouble());

    map.insert("slider_threshold", slider_threshold->property(SLIDER_VALUE).toDouble());

    return map;
}

void PlayStyleEdit::UpdatePresets(PresetsWindow *presets)
{
    this->presets = presets->GenPresetsMap();
    QStringList sets;

    for(auto p : this->presets) {
        sets.append(p.first);
    }

    //set name
    comboBox_set->setProperty(COMBOBOX_LIST, sets);
    if(currentSetName == "") {
        currentSetName = sets[0];
    }
    int set_index = 0;
    for(set_index = 0; set_index < 4; set_index++) {
        if(sets[set_index] == currentSetName) {
            break;
        }
    }
    comboBox_set->setProperty(COMBOBOX_INDEX, set_index);

    //preset name
    std::vector<QString> presetsVec;
    for(auto s : this->presets) {
        if(s.first == currentSetName) {
            presetsVec = s.second;
        }
    }

    QStringList presetsList;
    presetsList.append(presetsVec[0]);
    presetsList.append(presetsVec[1]);
    presetsList.append(presetsVec[2]);
    presetsList.append(presetsVec[3]);

    comboBox_preset->setProperty(COMBOBOX_LIST, presetsList);
    if(std::find(presetsVec.begin(), presetsVec.end(), currentPresetName) == presetsVec.end()) {
        currentPresetName = presetsList[0];
    }
    int preset_index = 0;
    for(preset_index = 0; preset_index < 4; preset_index++) {
        if(presetsVec[preset_index] == currentPresetName) {
            break;
        }
    }
    comboBox_preset->setProperty(COMBOBOX_INDEX, preset_index);
}

double PlayStyleEdit::Update(sound_processing::SoundProcessor* soundProcessor)
{
    QString setName = comboBox_set->property(COMBOBOX_VALUE).toString();
    if(setName != currentSetName) {
        currentSetName = setName;

        std::vector<QString> presetsVec;
        for(auto s : presets) {
            if(s.first == setName) {
                presetsVec = s.second;
            }
        }

        QStringList presets;
        presets.append(presetsVec[0]);
        presets.append(presetsVec[1]);
        presets.append(presetsVec[2]);
        presets.append(presetsVec[3]);

        comboBox_preset->setProperty(COMBOBOX_LIST, presets);
        currentPresetName = presets[0];
        comboBox_preset->setProperty(COMBOBOX_VALUE, currentPresetName);
    }
    currentPresetName = comboBox_preset->property(COMBOBOX_VALUE).toString();


    double match = 0.5;

    auto fft = soundProcessor->getNoteRecognition().getFFT();


    //low:
    float bass = 0;
    float FFT_BASS_max = 0;
    for(size_t i = FFT_BASS_MIN_FREQ / FFT_RES; i * FFT_RES < slider_bassFreq->property(SLIDER_VALUE).toDouble() && i < FFT_SIZE; i++) {
        FFT_BASS_max = std::max(FFT_BASS_max, fft[i]);
    }
    int FFT_BASS_counter = 0;
    for(size_t i = FFT_BASS_MIN_FREQ / FFT_RES; i * FFT_RES < slider_bassFreq->property(SLIDER_VALUE).toDouble() && i < FFT_SIZE; i++) {
        if(fft[i] > FFT_BASS_max * FFT_BASS_THRESHOLD) {
            bass += fft[i];
            FFT_BASS_counter++;
        }
    }
    bass *= slider_bassFactor->property(SLIDER_VALUE).toDouble() / std::max((double)FFT_BASS_counter, 0.001);
    double bassTarget = dial_bassTarget->property(DIAL_VALUE).toDouble();

    double bassMatch = 0;
    if(bassTarget >= 0.5) {
        bassMatch = bass - bassTarget + 1;
    } else {
        bassMatch = bassTarget - bass;
    }


    //high:
    float high = 0;
    float FFT_HIGH_max = 0;
    for(size_t i = slider_highFreq->property(SLIDER_VALUE).toDouble() / FFT_RES; i * FFT_RES < FFT_HIGH_TOP_FREQ && i < FFT_SIZE; i++) {
        FFT_HIGH_max = std::max(FFT_HIGH_max, fft[i]);
    }
    int FFT_HIGH_counter = 0;
    for(size_t i = slider_highFreq->property(SLIDER_VALUE).toDouble() / FFT_RES; i * FFT_RES < FFT_HIGH_TOP_FREQ && i < FFT_SIZE; i++) {
        if(fft[i] > FFT_HIGH_max * FFT_HIGH_THRESHOLD) {
            high += fft[i];
            FFT_HIGH_counter++;
        }
    }
    high *= slider_highFactor->property(SLIDER_VALUE).toDouble() / std::max((double)FFT_HIGH_counter, 0.001);
    double highTarget = dial_highTarget->property(DIAL_VALUE).toDouble();

    double highMatch = 0;
    if(highTarget >= 0.5) {
        highMatch = high - highTarget + 1;
    } else {
        highMatch = highTarget - high;
    }


    //match:
    match = highMatch + bassMatch;

    progressBar_threshold->setProperty(PROGRESS_BAR_VALUE, match);
    return match;
}

double PlayStyleEdit::getThreshold()
{
    return slider_threshold->property(SLIDER_VALUE).toDouble();
}

void PlayStyleEdit::Activate(hardware_ctrl::EffectController *controller, PresetsWindow *presets)
{
    background->setProperty(OPACITY, 0.4);
    auto p = presets->getPreset(comboBox_set->property(COMBOBOX_VALUE).toString(), comboBox_preset->property(COMBOBOX_VALUE).toString());
    if(p != nullptr) {
        controller->SetPreset(*p);
    }
}

void PlayStyleEdit::Disable()
{
    background->setProperty(OPACITY, 0.1);
}

///#####################################################################################

AutoSwitchSetWindowEdit::AutoSwitchSetWindowEdit(QString name, QQmlApplicationEngine *engine, QQuickItem *parent)
{
    this->name = name;

    //create component
    QQmlComponent comp(engine, parent);
    comp.loadUrl(SONG_EDIT_URL);

    //add element
    window = qobject_cast<QQuickItem *>(comp.create());
    engine->setObjectOwnership(window, QQmlEngine::JavaScriptOwnership);
    window->setParentItem(parent);
    window->setVisible(false);

    playStyleEdit_1 = new PlayStyleEdit("solo", window->findChild<QQuickItem*>(STYLE_EDIT_1));
    playStyleEdit_2 = new PlayStyleEdit("clean", window->findChild<QQuickItem*>(STYLE_EDIT_2));
    playStyleEdit_3 = new PlayStyleEdit("dirty", window->findChild<QQuickItem*>(STYLE_EDIT_3));

    headline = window->findChild<QQuickItem*>(SONG_HEADLINE);
    headline->setProperty(LABEL_TEXT, name);
}

AutoSwitchSetWindowEdit::AutoSwitchSetWindowEdit(QVariantMap map, QQmlApplicationEngine *engine, QQuickItem *parent)
{
    name = map["name"].toString();

    //create component
    QQmlComponent comp(engine, parent);
    comp.loadUrl(SONG_EDIT_URL);

    //add element
    window = qobject_cast<QQuickItem *>(comp.create());
    engine->setObjectOwnership(window, QQmlEngine::JavaScriptOwnership);
    window->setParentItem(parent);
    window->setVisible(false);

    playStyleEdit_1 = new PlayStyleEdit(map["playStyle_1"].toMap(), window->findChild<QQuickItem*>(STYLE_EDIT_1));
    playStyleEdit_2 = new PlayStyleEdit(map["playStyle_2"].toMap(), window->findChild<QQuickItem*>(STYLE_EDIT_2));
    playStyleEdit_3 = new PlayStyleEdit(map["playStyle_3"].toMap(), window->findChild<QQuickItem*>(STYLE_EDIT_3));

    headline = window->findChild<QQuickItem*>(SONG_HEADLINE);
    headline->setProperty(LABEL_TEXT, name);
}

QVariantMap AutoSwitchSetWindowEdit::GenMap()
{
    QVariantMap map;

    map.insert("name", name);
    map.insert("playStyle_1", playStyleEdit_1->GenMap());
    map.insert("playStyle_2", playStyleEdit_2->GenMap());
    map.insert("playStyle_3", playStyleEdit_3->GenMap());

    return map;
}

void AutoSwitchSetWindowEdit::Update(hardware_ctrl::EffectController* controller, sound_processing::SoundProcessor* soundProcessor, PresetsWindow* presets)
{
    double delta_1 = playStyleEdit_1->Update(soundProcessor) - playStyleEdit_1->getThreshold();
    double delta_2 = playStyleEdit_2->Update(soundProcessor) - playStyleEdit_2->getThreshold();
    double delta_3 = playStyleEdit_3->Update(soundProcessor) - playStyleEdit_3->getThreshold();

    if(autoModState) {
        if(delta_1 >= delta_2) {
            if(delta_1 >= delta_3) {
                if(delta_1 > 0) {
                    activate_1(controller, presets);
                }
            } else {
                if(delta_3 > 0) {
                    activate_3(controller, presets);
                }
            }
        } else {
            if(delta_2 >= delta_3) {
                if(delta_2 > 0) {
                    activate_2(controller, presets);
                }
            } else {
                if(delta_3 > 0) {
                    activate_3(controller, presets);
                }
            }
        }
    }
}

void AutoSwitchSetWindowEdit::UpdatePresets(PresetsWindow *presets)
{
    playStyleEdit_1->UpdatePresets(presets);
    playStyleEdit_2->UpdatePresets(presets);
    playStyleEdit_3->UpdatePresets(presets);
}

void AutoSwitchSetWindowEdit::Show()
{
    window->setVisible(true);
    playStyleEdit_1->Disable();
    playStyleEdit_2->Disable();
    playStyleEdit_3->Disable();
}

void AutoSwitchSetWindowEdit::Hide()
{
    window->setVisible(false);
}

void AutoSwitchSetWindowEdit::activate_1(hardware_ctrl::EffectController *controller, PresetsWindow* presets)
{
    playStyleEdit_1->Activate(controller, presets);
    playStyleEdit_2->Disable();
    playStyleEdit_3->Disable();
}

void AutoSwitchSetWindowEdit::activate_2(hardware_ctrl::EffectController *controller, PresetsWindow* presets)
{
    playStyleEdit_1->Disable();
    playStyleEdit_2->Activate(controller, presets);
    playStyleEdit_3->Disable();
}

void AutoSwitchSetWindowEdit::activate_3(hardware_ctrl::EffectController *controller, PresetsWindow *presets)
{
    playStyleEdit_1->Disable();
    playStyleEdit_2->Disable();
    playStyleEdit_3->Activate(controller, presets);
}

void AutoSwitchSetWindowEdit::autoMod(bool on)
{
    autoModState = on;
}
