#ifndef EFFECTCONTROLLER_H
#define EFFECTCONTROLLER_H

// todo: work with preset

#include <vector>
#include <map>
#include "potentiometer.h"
#include "effect.h"
#include <functional>
#include "gpioread.h"
#include "preset.h"

namespace hardware_ctrl {
    class EffectController
    {
    public:
        EffectController(int incPin, int udPin);
        ~EffectController();

        void Initialize();

        Effect* GetEffect(std::string name);
        void AddEffect(std::string name, Effect* effect);
        void AddButton(std::string name, int ioPin);
        void AddButtonPressEvent(std::string buttonName, std::function<void(EffectController* controller)> func);
        void AddButtonReleaseEvent(std::string buttonName, std::function<void(EffectController* controller)> func);

        void LoadPreset(Preset preset);

        void SetAllToValue();
        void SetAllToValueSmooth(size_t time_ms, size_t resolution = 100);
        void SetAllToValue_Long();

        void UpdateButtons();

        uint64_t GetButtonsState();

        void ButtonChanged(uint64_t changedButtons);

        void SetPreset(Preset p);

    private:
        void ForEachPotentiometer(std::function<void(Potentiometer*)> func);

    private:
        std::map<std::string, std::vector<std::function<void(EffectController* controller)>>*> m_onButonPress;
        std::map<std::string, std::vector<std::function<void(EffectController* controller)>>*> m_onButonRelease;
        std::map<std::string, Effect*> m_effects;
        GpioControl* m_ud;
        GpioControl* m_inc;
        std::map<std::string, GpioRead*> m_buttons;
        uint64_t m_buttonsState = 0;
    };
}

#endif // EFFECTCONTROLLER_H
