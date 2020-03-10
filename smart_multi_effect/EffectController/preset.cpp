#include "preset.h"

using namespace hardware_ctrl;


Preset::Preset()
{

}


Preset::Preset(std::string path)
{
    Load(path);
}

Preset::Preset(std::list<EffectInfo> effects, size_t time_ms, size_t resolution)
{
    Set(time_ms, resolution, effects);
}

void Preset::Load(std::string path)
{
    //todo
}

void Preset::Set(size_t time_ms, size_t resolution, std::list<EffectInfo> effects)
{
    this->time_ms = time_ms;
    this->resolution = resolution;
    this->effects = effects;
}
