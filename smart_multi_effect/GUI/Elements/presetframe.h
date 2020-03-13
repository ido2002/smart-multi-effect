#ifndef PRESETFRAME_H
#define PRESETFRAME_H

#include <QQuickItem>
#include "EffectController/preset.h"

struct Preset
{
    Preset(QString name) {
        this->name = name;
    }
    QString name;
    hardware_ctrl::Preset preset;
};

class PresetFrame
{
public:
    PresetFrame(QString name);

    QString name;

    Preset p1;
    Preset p2;
    Preset p3;
    Preset p4;
};

#endif // PRESETFRAME_H
