#include "effect_gui.h"

#include "conf.h"

using namespace GUI_elements;
using namespace CONF::GUI_PARAMETERS;
using namespace EFFECT_EDIT;
using namespace GENERAL_GUI_PROPERTIES_NAMES;

using layoutElements = hardware_ctrl::Effect::EffectControlLayoutEllements;

Effect_gui::Effect_gui()
{

}

Effect_gui::Effect_gui(QString effectName, QQuickItem *parent, QQmlApplicationEngine *engine, hardware_ctrl::Effect *effect)
{
    initialize(effectName, parent, engine, effect);
}

void Effect_gui::initialize(QString effectName, QQuickItem *parent, QQmlApplicationEngine *engine, hardware_ctrl::Effect *effect)
{
    m_effect = effect;
    //create component
    QQmlComponent comp(engine, parent);
    comp.loadUrl(EFFECT_EDIT3_URL);

    //add element
    QQuickItem *Instance = qobject_cast<QQuickItem *>(comp.create());
    engine->setObjectOwnership(Instance,QQmlEngine::JavaScriptOwnership);
    Instance->setParentItem(parent);
    m_item = Instance;

    //set name lable
    Instance->childItems()[0]->findChild<QQuickItem*>(EFFECT_LABLE_NAME)->setProperty(LABLE_TEXT, effectName);

    //set dials
    {
        size_t i = 1;
        for(auto p : effect->m_potentiometers) {
            QString dialName = "error";
            switch (i) {
            case 1:
                dialName = DIAL1_NAME;
                break;
            case 2:
                dialName = DIAL2_NAME;
                break;
            case 3:
                dialName = DIAL3_NAME;
                break;
            case 4:
                dialName = DIAL4_NAME;
                break;
            case 5:
                dialName = DIAL5_NAME;
                break;
            case 6:
                dialName = DIAL6_NAME;
                break;
            }
            if(dialName == "error") {
                continue;
            }
            m_dials.insert(std::pair<layoutElements, QQuickItem*>(p.first, m_item->childItems()[0]->findChild<QQuickItem*>(dialName)));
            m_dials.find(p.first)->second->findChild<QQuickItem*>(TEXT_LABLE_NAME)->setProperty(LABLE_TEXT, QString::fromStdString(hardware_ctrl::Effect::LayoutEllementToString(p.first)));
            i++;
        }
    }

    //set switch
    m_switch = m_item->childItems()[0]->findChild<QQuickItem*>(SWITCH_NAME);
}

double Effect_gui::ReadDial(hardware_ctrl::Effect::EffectControlLayoutEllements dialElement)
{
    auto dial = m_dials.find(dialElement)->second;
    if(dial == nullptr) {
        return 0;
    }
    return dial->property(DIAL_VALUE).toDouble();
}

void Effect_gui::SetDial(hardware_ctrl::Effect::EffectControlLayoutEllements dialElement, double value)
{
    auto dial = m_dials.find(dialElement)->second;
    if(dial == nullptr) {
        return;
    }
    dial->setProperty(DIAL_VALUE, value);
}

bool Effect_gui::ReadSwitch()
{
    return m_switch->property(SWITCH_STATE).toBool();
}

void Effect_gui::SetSwitch(bool value)
{
    m_switch->setProperty(SWITCH_STATE, value);
}

bool Effect_gui::update(bool setTarget, bool activateSwitch)
{

}
