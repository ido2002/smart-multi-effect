#ifndef EFFECTCONTROLLER_H
#define EFFECTCONTROLLER_H

// todo: work with preset

#include <vector>
#include <map>
#include "potentiometer.h"
#include "effect.h"
#include <functional>
#include "gpioread.h"


class EffectController
{
public:
    EffectController(int incPin, int udPin);
    ~EffectController();

    Effect* GetEffect(std::string name);
    void AddEffect(std::string name, Effect* effect);
    void AddButton(std::string name, int ioPin);
    void AddButtonEvent(std::string buttonName, std::function<void(EffectController* controller)> func);

    void SetAllToValue();
    void SetAllToValue_Long();

    void UpdateButtons();

    uint64_t GetButtonsState();

    void ButtonChanged(uint64_t changedButtons);


private:
    void ForEachPotentiometer(std::function<void(Potentiometer*)> func);

private:
    std::map<std::string, std::vector<std::function<void(EffectController* controller)>>*> m_onButonPress;
    std::map<std::string, Effect*> m_effects;
    GpioControl* m_ud;
    GpioControl* m_inc;
    std::map<std::string, GpioRead*> m_buttons;
    uint64_t m_buttonsState = 0;
};

#endif // EFFECTCONTROLLER_H
