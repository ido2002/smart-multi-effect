#ifndef EFFECT_H
#define EFFECT_H

#include <QQuickItem>
#include <QString>
#include <list>
#include <QQmlApplicationEngine>

#include <EffectController/effect.h>

namespace GUI_elements {
    class Effect_gui
    {
    public:
        Effect_gui();
        Effect_gui(QString effectName, QQuickItem* parent, QQmlApplicationEngine *engine, hardware_ctrl::Effect* effect);

        void initialize(QString effectName, QQuickItem *parent, QQmlApplicationEngine *engine, hardware_ctrl::Effect* effect);

        double ReadDial(hardware_ctrl::Effect::EffectControlLayoutEllements dialElement);
        void SetDial(hardware_ctrl::Effect::EffectControlLayoutEllements dialElement, double value);

        bool ReadSwitch();
        void SetSwitch(bool value);

        bool update(bool setTarget, bool activateSwitch); //return true if there is a change

    private:
        QQuickItem* m_item = nullptr;
        QQuickItem* m_switch = nullptr;
        std::map<hardware_ctrl::Effect::EffectControlLayoutEllements, QQuickItem*> m_dials;
        hardware_ctrl::Effect* m_effect = nullptr;
    };
}

#endif // EFFECT_H
