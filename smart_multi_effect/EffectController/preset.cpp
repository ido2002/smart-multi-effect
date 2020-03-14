#include "preset.h"
#include "conf.h"

#include <iostream>

using namespace hardware_ctrl;


Preset::Preset()
{

}


Preset::Preset(std::string path)
{
    Load(path);
}

Preset::Preset(std::list<EffectInfo*> effects, size_t time_ms, size_t resolution)
{
    Set(time_ms, resolution, effects);
}

void Preset::Load(std::string path)
{
    //todo
}

void Preset::Set(size_t time_ms, size_t resolution, std::list<EffectInfo*> effects)
{
    this->time_ms = time_ms;
    this->resolution = resolution;
    for(auto e : effects) {
        this->effects.insert(std::pair<std::string, EffectInfo*>(e->name, e));
    }
}

EffectInfo* Preset::getEffect(std::string name)
{
    return effects.find(name)->second;
}

EffectInfo::EffectInfo(ColorSet colors, std::string name, bool state, std::map<Effect::EffectControlLayoutEllements, int> potentiometers)
 : colors(colors)
{
    this->name = name;
    this->state = state;
    this->potentiometers = potentiometers;
}
