#ifndef PRESET_H
#define PRESET_H

#include "effect.h"
#include <map>
#include <list>
#include <string>

namespace hardware_ctrl {
    struct EffectInfo
    {
        std::string name;
        bool state;
        std::map<std::string/*name*/, double/*value*/> potentiometers;
    };

    class Preset
    {
    public:
        Preset();
        Preset(std::string path);
        Preset(size_t time_ms, size_t resolution, std::list<EffectInfo> effects);

        void Load(std::string path);
        void Set(size_t time_ms, size_t resolution, std::list<EffectInfo> effects);

    public:
        size_t time_ms;
        size_t resolution;
        std::list<EffectInfo> effects;
    };
}
#endif // PRESET_H
