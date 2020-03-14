#include "effect_gui.h"

#include "conf.h"

using namespace GUI_elements;
using namespace CONF::GUI_PARAMETERS;
using namespace EFFECT_EDIT;
using namespace GENERAL_GUI_PROPERTIES_NAMES;

using layoutElements = hardware_ctrl::Effect::EffectControlLayoutEllements;


Effect_gui::Effect_gui(hardware_ctrl::EffectInfo* effect, QQuickItem *parent, QQmlApplicationEngine *engine)
{
    this->effect = effect;
    name = effect->name;

    //create component
    QQmlComponent comp(engine, parent);
    comp.loadUrl(EFFECT_EDIT3_URL);

    //add element
    QQuickItem *Instance = qobject_cast<QQuickItem *>(comp.create());
    engine->setObjectOwnership(Instance,QQmlEngine::JavaScriptOwnership);
    Instance->setParentItem(parent);
    item = Instance;

    auto rect = item->childItems()[0]->findChild<QQuickItem*>(BACKGROUND_RECT);
    rect->setProperty(COLOR, effect->colors.backGroundColor);

    //set name lable
    Instance->childItems()[0]->findChild<QQuickItem*>(EFFECT_LABLE_NAME)->setProperty(LABLE_TEXT, QString::fromStdString(effect->name));
    Instance->childItems()[0]->findChild<QQuickItem*>(EFFECT_LABLE_NAME)->setProperty(COLOR, effect->colors.fontColor);

    //set dials
    {
        size_t i = 1;
        for(auto p : effect->potentiometers) {
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
            m_dials.insert(std::pair<layoutElements, QQuickItem*>(p.first, item->childItems()[0]->findChild<QQuickItem*>(dialName)));
            m_dials.find(p.first)->second->findChild<QQuickItem*>(TEXT_LABLE_NAME)->setProperty(LABLE_TEXT, QString::fromStdString(hardware_ctrl::Effect::LayoutEllementToString(p.first)));

            m_dials.find(p.first)->second->findChild<QQuickItem*>(DIAL_NAME)->setProperty(COLOR, effect->colors.dialsColor);
            m_dials.find(p.first)->second->findChild<QQuickItem*>(VALUE_LABLE_NAME)->setProperty(COLOR, effect->colors.fontColor);
            m_dials.find(p.first)->second->findChild<QQuickItem*>(TEXT_LABLE_NAME)->setProperty(COLOR, effect->colors.fontColor);

            i++;
        }
    }

    //set switch
    m_switch = item->childItems()[0]->findChild<QQuickItem*>(SWITCH_NAME);

    RefreshGui();
}

void Effect_gui::RefreshGui()
{
    SetSwitch(effect->state);
    for(auto p : effect->potentiometers) {
        SetDial(p.first, p.second);
    }
}

double Effect_gui::ReadDial(hardware_ctrl::Effect::EffectControlLayoutEllements dialElement)
{
    auto dial = m_dials.find(dialElement)->second;
    if(dial == nullptr) {
        return 0;
    }
    return dial->findChild<QQuickItem*>(DIAL_NAME)->property(DIAL_VALUE).toDouble() * 100;
}

void Effect_gui::SetDial(hardware_ctrl::Effect::EffectControlLayoutEllements dialElement, double value)
{
    auto dial = m_dials.find(dialElement)->second;
    if(dial == nullptr) {
        return;
    }
    dial->findChild<QQuickItem*>(DIAL_NAME)->setProperty(DIAL_VALUE, value / 100);
}

bool Effect_gui::ReadSwitch()
{
    return m_switch->property(SWITCH_STATE).toBool();
}

void Effect_gui::SetSwitch(bool value)
{
    m_switch->setProperty(SWITCH_STATE, value);
}

