#ifndef PRESET_H
#define PRESET_H

#include "effect.h"
#include <map>
#include <list>
#include <string>

namespace hardware_ctrl {
    struct EffectInfo
    {
        EffectInfo();
        EffectInfo(std::string name, bool state, std::map<Effect::EffectControlLayoutEllements, int/*value*/> potentiometers);
        std::string name;
        bool state;
        std::map<Effect::EffectControlLayoutEllements, int/*value*/> potentiometers;
    };

    class Preset
    {
    public:
        Preset();
        Preset(std::string path);
        Preset(std::list<EffectInfo> effects, size_t time_ms = 0, size_t resolution = 0);

        void Load(std::string path);
        void Set(size_t time_ms, size_t resolution, std::list<EffectInfo> effects);

    public:
        size_t time_ms = 0;
        size_t resolution = 0;
        std::list<EffectInfo> effects;
    };
}
#endif // PRESET_H
