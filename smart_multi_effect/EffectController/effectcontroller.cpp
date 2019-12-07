#include "effectcontroller.h"

#include <unistd.h>
#include <fcntl.h>
#include <iostream>

EffectController::EffectController(int incPin, int udPin) :
    m_ud(udPin, true), m_inc(incPin, false)
{

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

void EffectController::SetAllToValue()
{
    int count = 0;
    ForEachPotentiometer([&](Potentiometer*){ count ++; });

    //up
    m_ud.Write(true);
    for(int i = 0; i < 100; i++) {
        int okCount = 0;
        ForEachPotentiometer([&](Potentiometer* p){
            if(p->Check(true))
                okCount++;
        });
        if(okCount >= count) {
            break;
        }
        m_inc.Tick(15);
    }

    //down
    m_ud.Write(false);
    for(int i = 0; i < 100; i++) {
        int okCount = 0;
        ForEachPotentiometer([&](Potentiometer* p){
            if(p->Check(false))
                okCount++;
        });
        if(okCount >= count) {
            break;
        }
        m_inc.Tick(15);
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
    m_ud.Write(true);
    for(int i = 0; i < 110; i++) {
        m_inc.Tick(15);
    }

    //down
    m_ud.Write(false);
    for(int i = 0; i < 100; i++) {
        int okCount = 0;
        ForEachPotentiometer([&](Potentiometer* p){
            if(p->Check(false))
                okCount++;
        });
        if(okCount >= count) {
            break;
        }
        m_inc.Tick(15);
    }
}

void EffectController::ForEachPotentiometer(std::function<void (Potentiometer *)> func)
{
    for(auto e : m_effects) {
        for(auto p : e.second->m_potentiometers) {
            func(p.second);
        }
    }
}
