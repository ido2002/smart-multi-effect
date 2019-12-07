#include "effect.h"
#include <iostream>

Effect::Effect(int ioPin, Effect::EffectType effectType, uint64_t layoutElements) :
    m_relay(new GpioControl(ioPin, true)), m_effectType(effectType), m_layoutElements(layoutElements)
{

}

Effect::~Effect()
{
    delete m_relay;
}

bool Effect::SetPotentiometer(Effect::EffectControlLayoutEllements element, int ioPin)
{
    if(!(element & m_layoutElements)) {
        std::cout << "element isn't in layoutElements" << std::endl;
        return false;
    }
    Potentiometer* p = new Potentiometer(ioPin);
    m_potentiometers.insert(std::pair<EffectControlLayoutEllements, Potentiometer*>(element, p));
    return true;
}

Potentiometer *Effect::GetPotentiometer(Effect::EffectControlLayoutEllements element)
{
    if(element & m_layoutElements) {
        auto it = m_potentiometers.find(element);
        if(it == m_potentiometers.end())
            return nullptr;
        return it->second;
    }
    else
        return nullptr;
}

void Effect::On()
{
    m_relay->Write(true);
}

void Effect::Off()
{
    m_relay->Write(false);
}
