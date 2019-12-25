#include "effectcontroller.h"

#include <unistd.h>
#include <fcntl.h>
#include <iostream>
#include <thread>

EffectController::EffectController(int incPin, int udPin) :
    m_ud(new GpioControl(udPin, true)), m_inc(new GpioControl(incPin, false))
{

}

EffectController::~EffectController()
{
    delete m_ud;
    delete m_inc;
}

Effect *EffectController::GetEffect(std::string name)
{
    auto it = m_effects.find(name);
    if(it == m_effects.end())
        return nullptr;
    return it->second;
}

void EffectController::AddEffect(std::string name, Effect* effect)
{
    m_effects.insert(std::pair<std::string, Effect*>(name, effect));
}

void EffectController::AddButton(std::string name, int ioPin)
{
    m_buttons.insert(std::pair<std::string, GpioRead*>(name, new GpioRead(ioPin, true, name)));
}

void EffectController::AddButtonEvent(std::string buttonName, std::function<void(EffectController* controller)> func)
{
    if(m_buttons.find(buttonName) != m_buttons.end()) {
        auto b = m_onButonPress.find(buttonName);
        if(b == m_onButonPress.end()) {
            m_onButonPress.insert(std::pair<std::string, std::vector<std::function<void(EffectController* controller)>>*>
                                  (buttonName, new std::vector<std::function<void(EffectController* controller)>>));
            b = m_onButonPress.find(buttonName);
        }
        b->second->push_back(func);
    }
}

void EffectController::SetAllToValue()
{
    int count = 0;
    ForEachPotentiometer([&](Potentiometer*){ count ++; });

    //up
    m_ud->Write(true);
    for(int i = 0; i < 100; i++) {
        int okCount = 0;
        ForEachPotentiometer([&](Potentiometer* p){
            if(p->Check(true))
                okCount++;
        });
        if(okCount >= count) {
            break;
        }
        m_inc->Tick(15);
    }

    //down
    m_ud->Write(false);
    for(int i = 0; i < 100; i++) {
        int okCount = 0;
        ForEachPotentiometer([&](Potentiometer* p){
            if(p->Check(false))
                okCount++;
        });
        if(okCount >= count) {
            break;
        }
        m_inc->Tick(15);
    }
}

void EffectController::SetAllToValue_Long()
{
    int count = 0;
    ForEachPotentiometer([&](Potentiometer* p){
        count ++;
        p->SetCurrentValue(100);
        p->CS(true);
    });

    //up
    m_ud->Write(true);
    for(int i = 0; i < 110; i++) {
        m_inc->Tick(15);
    }

    //down
    m_ud->Write(false);
    for(int i = 0; i < 100; i++) {
        int okCount = 0;
        ForEachPotentiometer([&](Potentiometer* p){
            if(p->Check(false))
                okCount++;
        });
        if(okCount >= count) {
            break;
        }
        m_inc->Tick(15);
    }
}

void EffectController::UpdateButtons()
{
    size_t count = 0;
    uint64_t buttonsState = 0;
    for (auto it = m_buttons.begin(); it != m_buttons.end(); it++) {
        buttonsState |= static_cast<uint64_t>(it->second->Read() ? 1 : 0) << count;
        count++;
    }
    uint64_t difrence = buttonsState ^ m_buttonsState;
    m_buttonsState = buttonsState;
    if(difrence) {
        ButtonChanged(difrence);
    }
}

uint64_t EffectController::GetButtonsState()
{
    return m_buttonsState;
}

void EffectController::ForEachPotentiometer(std::function<void (Potentiometer *)> func)
{
    for(auto e : m_effects) {
        for(auto p : e.second->m_potentiometers) {
            func(p.second);
        }
    }
}

void EffectController::ButtonChanged(uint64_t changedButtons)
{
    size_t count = 0;
    for (auto it = m_buttons.begin(); it != m_buttons.end(); it++) {
        if((changedButtons >> count)&1) {
            std::cout << it->second->GetName() << ": " << ((m_buttonsState >> count)&1) << std::endl;
            if(((m_buttonsState >> count)&1) == 1) {
                auto onButtonPress = m_onButonPress.find(it->second->GetName());
                if(onButtonPress == m_onButonPress.end()) {
                    continue;
                }
                auto functions = onButtonPress->second;
                for (auto f : *functions) {
                    f(this);
                }
            }
        }
        count++;
    }
}
