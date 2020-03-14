#ifndef PRESET_H
#define PRESET_H

#include "effect.h"
#include <map>
#include <list>
#include <string>
#include <QString>

namespace hardware_ctrl {
    struct ColorSet
    {
        ColorSet(QString backGroundColor, QString dialsColor, QString fontColor) {
            this->fontColor = fontColor;
            this->dialsColor = dialsColor;
            this->backGroundColor = backGroundColor;
        }

        QString backGroundColor;
        QString dialsColor;
        QString fontColor;
    };

    struct EffectInfo
    {
        EffectInfo(ColorSet colors, std::string name, bool state, std::map<Effect::EffectControlLayoutEllements, int/*value*/> potentiometers);
        std::string name;
        bool state;
        std::map<Effect::EffectControlLayoutEllements, int/*value*/> potentiometers;
        ColorSet colors;
    };

    class Preset
    {
    public:
        Preset();
        Preset(std::string path);
        Preset(std::list<EffectInfo*> effects, size_t time_ms = 0, size_t resolution = 0);

        void Load(std::string path);
        void Set(size_t time_ms, size_t resolution, std::list<EffectInfo*> effects);

        EffectInfo* getEffect(std::string name);

    public:
        size_t time_ms = 0;
        size_t resolution = 0;
        std::map<std::string, EffectInfo*> effects;
    };
}
#endif // PRESET_H
