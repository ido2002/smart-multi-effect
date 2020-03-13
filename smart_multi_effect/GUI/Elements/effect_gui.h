#ifndef EFFECT_H
#define EFFECT_H

#include <QQuickItem>
#include <QString>
#include <list>
#include <QQmlApplicationEngine>

#include <EffectController/preset.h>

namespace GUI_elements {
    class Effect_gui
    {
    public:
        Effect_gui(hardware_ctrl::EffectInfo* effect, QQuickItem* parent, QQmlApplicationEngine *engine);

        void RefreshGui();

        double ReadDial(hardware_ctrl::Effect::EffectControlLayoutEllements dialElement);
        void SetDial(hardware_ctrl::Effect::EffectControlLayoutEllements dialElement, double value);

        bool ReadSwitch();
        void SetSwitch(bool value);

        std::string getName() { return name; }

    private:
        hardware_ctrl::EffectInfo* effect = nullptr;
        std::string name;
        QQuickItem* m_item = nullptr;
        QQuickItem* m_switch = nullptr;
        std::map<hardware_ctrl::Effect::EffectControlLayoutEllements, QQuickItem*> m_dials;
    };
}

#endif // EFFECT_H
