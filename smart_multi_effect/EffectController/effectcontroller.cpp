#include "effectcontroller.h"

#include "conf.h"

#include <unistd.h>
#include <fcntl.h>
#include <iostream>
#include <thread>

using namespace hardware_ctrl;

EffectController::EffectController(int incPin, int udPin) :
    m_ud(new GpioControl(udPin, /*true*/ false)), m_inc(new GpioControl(incPin, false))
{

}

EffectController::~EffectController()
{
    delete m_ud;
    delete m_inc;
}

void initialPotentiometers(Effect* e, uint64_t potentiometers)
{
    using namespace CONF::HARDWARE;
    for(uint i = 0; i < POTENTIOMETER_COUNT; i++) {
        if(potentiometers & 1 << i) {
            switch(i)
            {
            case 0:
                e->SetPotentiometer(P1_TYPE, P1_PIN);
                break;
            case 1:
                e->SetPotentiometer(P2_TYPE, P2_PIN);
                break;
            case 2:
                e->SetPotentiometer(P3_TYPE, P3_PIN);
                break;
            case 3:
                e->SetPotentiometer(P4_TYPE, P4_PIN);
                break;
            case 4:
                e->SetPotentiometer(P5_TYPE, P5_PIN);
                break;
            case 5:
                e->SetPotentiometer(P6_TYPE, P6_PIN);
                break;
            }
        }
    }
}

void EffectController::Initialize()
{
    using namespace CONF::HARDWARE;
    Effect* e1 = new Effect(RELAY_1, EFFECT_1_TYPE, EFFECT_1_LAYOUT);
    initialPotentiometers(e1, EFFECT_1_POTENTIOMETERS);
    AddEffect(EFFECT_1_NAME, e1);

    Effect* e2 = new Effect(RELAY_2, EFFECT_2_TYPE, EFFECT_2_LAYOUT);
    initialPotentiometers(e2, EFFECT_2_POTENTIOMETERS);
    AddEffect(EFFECT_2_NAME, e2);

    Effect* e3 = new Effect(RELAY_3, EFFECT_3_TYPE, EFFECT_3_LAYOUT);
    initialPotentiometers(e3, EFFECT_3_POTENTIOMETERS);
    AddEffect(EFFECT_3_NAME, e3);
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

void EffectController::AddButtonPressEvent(std::string buttonName, std::function<void(EffectController* controller)> func)
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


void EffectController::AddButtonReleaseEvent(std::string buttonName, std::function<void(EffectController* controller)> func)
{
    if(m_buttons.find(buttonName) != m_buttons.end()) {
        auto b = m_onButonRelease.find(buttonName);
        if(b ==  m_onButonRelease.end()) {
             m_onButonRelease.insert(std::pair<std::string, std::vector<std::function<void(EffectController* controller)>>*>
                                  (buttonName, new std::vector<std::function<void(EffectController* controller)>>));
            b =  m_onButonRelease.find(buttonName);
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

void EffectController::SetAllToValueSmooth(size_t time_ms, size_t resolution)
{
    int count = 0;
    ForEachPotentiometer([&](Potentiometer*) { count ++; });
    std::vector<uint> targets(count);
    std::vector<uint> initialValues(count);
    {
        size_t i = 0;
        ForEachPotentiometer([&](Potentiometer* p) {
            targets[i] = p->GetTarget();
            targets[i] = p->GetValue();
            i++;
        });
    }
    for(size_t i = 0; i <= resolution; i++) {
        {
            size_t i = 0;
            ForEachPotentiometer([&](Potentiometer* p) {
                p->SetTarget(initialValues[i] + (targets[i] - initialValues[i])*i/resolution);
                i++;
            });
        }
        SetAllToValue();
        usleep(time_ms * 1000 / resolution);
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
            if(((m_buttonsState >> count)&1) == 1) { //pressed
                auto onButtonPress = m_onButonPress.find(it->second->GetName());
                if(onButtonPress == m_onButonPress.end()) {
                    continue;
                }
                auto functions = onButtonPress->second;
                for (auto f : *functions) {
                    f(this);
                }
            } else { //released
                auto onButtonRelease = m_onButonRelease.find(it->second->GetName());
                if(onButtonRelease == m_onButonRelease.end()) {
                    continue;
                }
                auto functions = onButtonRelease->second;
                for (auto f : *functions) {
                    f(this);
                }
            }
        }
        count++;
    }
}

void EffectController::SetPreset(Preset preset)
{
    std::map<std::string, bool> effectStates;
    for(auto e : m_effects) {
        effectStates.insert(std::pair<std::string, bool>(e.first, false));
    }
    for(auto e : preset.effects) {
        effectStates[e.second->name] = e.second->state;
    }

    for(auto e : effectStates) {
        if(m_effects.find(e.first) == m_effects.end())
            continue;
        if(e.second) {
            m_effects[e.first]->On();
        } else {
            m_effects[e.first]->Off();
        }
    }


    if(preset.resolution > 0 && preset.time_ms > 0) {
        using pMap = std::map<Effect::EffectControlLayoutEllements, int>;
        using pPair = std::pair<Effect::EffectControlLayoutEllements, int>;

        std::map<std::string, pMap> targets_delta;
        std::map<std::string, pMap> initial_values;

        for(auto e : preset.effects) {
            if(m_effects.find(e.first) == m_effects.end()) {
                std::cout << e.first << "does not exist" << std::endl;
                continue;
            }
            pMap effectDelta;
            pMap effectInitial;
            for(auto p : e.second->potentiometers) {
                auto effect = GetEffect(e.second->name)->GetPotentiometer(p.first);
                if(effect) {
                    effectDelta.insert(pPair(p.first, p.second - effect->GetValue()));
                    effectInitial.insert(pPair(p.first, effect->GetValue()));
                }
            }
            targets_delta.insert(std::pair<std::string, pMap>(e.second->name, effectDelta));
            initial_values.insert(std::pair<std::string, pMap>(e.second->name, effectDelta));
        }

        for (int i = 0; i < 100; i += preset.resolution) {
            usleep(preset.time_ms * 1000/(100 / preset.resolution));
            for (auto e : targets_delta) {
                for(auto p : e.second) {
                    auto potentiometer = m_effects[e.first]->GetPotentiometer(p.first);
                    auto pInitial = initial_values[e.first][p.first];
                    if(potentiometer) {
                        potentiometer->SetTarget(pInitial + p.second * i * preset.resolution / 100); //not good yet
                    }
                }
            }
            SetAllToValue();
        }
    }

    for (auto e : preset.effects) {
        if(m_effects.find(e.first) == m_effects.end()) {
            std::cout << e.first << "does not exist" << std::endl;
            continue;
        }
        for(auto p : e.second->potentiometers) {
            if(m_effects[e.second->name]->GetPotentiometer(p.first)) {
                m_effects[e.second->name]->GetPotentiometer(p.first)->SetTarget(p.second);
            }
        }
    }

    SetAllToValue();
}
