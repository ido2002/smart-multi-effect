#include "effect.h"
#include <iostream>

using namespace hardware_ctrl;

using le = Effect::EffectControlLayoutEllements;

std::string Effect::LayoutEllementToString(Effect::EffectControlLayoutEllements element)
{
    switch (element) {
    case le::Low:
        return "Low";
    case le::Mid:
        return "Mid";
    case le::Mix:
        return "Mix";
    case le::Non:
        return "Non";
    case le::Gain:
        return "Gain";
    case le::High:
        return "High";
    case le::Rate:
        return "Rate";
    case le::Tone:
        return "Tone";
    case le::Depth:
        return "Depth";
    case le::Width:
        return "Width";
    case le::Manual:
        return "Manual";
    case le::Volume:
        return "Volume";
    case le::Other1:
        return "Other1";
    case le::Other2:
        return "Other2";
    case le::Other3:
        return "Other3";
    case le::Other4:
        return "Other4";
    case le::Other5:
        return "Other5";
    case le::Other6:
        return "Other6";
    }
    return "error";
}

Effect::Effect(int ioPin, Effect::EffectType effectType, uint64_t layoutElements) :
    m_relay(new GpioControl(ioPin, true)), m_effectType(effectType), m_layoutElements(layoutElements)
{

}

Effect::~Effect()
{
    delete m_relay;
}

bool Effect::SetPotentiometer(Effect::EffectControlLayoutEllements element, uint8_t ioPin)
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
