#ifndef EFFECTCONTROLLER_H
#define EFFECTCONTROLLER_H

#include <vector>
#include <map>
#include "potentiometer.h"
#include "effect.h"
#include <functional>

class EffectController
{

public:
    EffectController(int incPin, int udPin);

    Effect* GetEffect(std::string name);
    void AddEffect(std::string name, Effect* effect);

    void SetAllToValue();
    void SetAllToValue_Long();

private:
    void ForEachPotentiometer(std::function<void(Potentiometer*)> func);

private:
    std::map<std::string, Effect*> m_effects;
    GpioControl m_ud;
    GpioControl m_inc;
};

#endif // EFFECTCONTROLLER_H
