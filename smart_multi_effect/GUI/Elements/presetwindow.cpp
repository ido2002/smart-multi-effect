#include "presetwindow.h"
#include "conf.h"

using namespace CONF;
using namespace GUI_PARAMETERS;
using namespace GENERAL_GUI_PROPERTIES_NAMES;
using namespace PRESET_EDIT_PAGE;

using namespace GUI_elements;

PresetWindow::PresetWindow(QString name)
{
    this->name = name;
}

void PresetWindow::ShowActivePreset()
{
    Hide();

    if(activePreset == nullptr) {
        activePreset = p1;
    }
    if(activePreset) {
        activePreset->Show();
    }
}

void PresetWindow::Hide()
{
    if(p1) {
        p1->Hide();
    }
    if(p2) {
        p2->Hide();
    }
    if(p3) {
        p3->Hide();
    }
    if(p4) {
        p4->Hide();
    }
}

///##########################################################################

Preset::Preset(QString name, hardware_ctrl::Preset* preset, QQmlApplicationEngine *engine, QQuickItem *parent)
{
    this->name = name;
    this->preset = preset;

    //create component
    QQmlComponent comp(engine, parent);
    comp.loadUrl(PRESET_EDIT_URL);

    //add element
    editWindow = qobject_cast<QQuickItem *>(comp.create());
    engine->setObjectOwnership(editWindow, QQmlEngine::JavaScriptOwnership);
    editWindow->setParentItem(parent);
    editWindow->setVisible(false);

    editWindow->childItems()[0]->findChild<QQuickItem*>(PRESET_HEADLINE)->setProperty(LABLE_TEXT, name);

    //setup effects
    int e_index = 0;
    for(auto e : this->preset->effects) {
        e_index++;
        QQuickItem* parent = nullptr;
        switch (e_index) {
        case 1:
            parent = editWindow->findChild<QQuickItem*>(EFFECT_1);
            break;
        case 3:
            parent = editWindow->findChild<QQuickItem*>(EFFECT_2);
            break;
        case 2:
            parent = editWindow->findChild<QQuickItem*>(EFFECT_3);
            break;
        case 4:
            parent = editWindow->findChild<QQuickItem*>(EFFECT_4);
            break;
        case 6:
            parent = editWindow->findChild<QQuickItem*>(EFFECT_5);
            break;
        case 5:
            parent = editWindow->findChild<QQuickItem*>(EFFECT_6);
            break;
        }
        Effect_gui* eg = new Effect_gui(e.second, parent, engine);
        effects.push_back(eg);
    }

    //editTime = editWindow->childItems()[0]->childItems()[0]->findChild<QQuickItem*>(TIME_SLIDER);
    //editResolution = editWindow->childItems()[0]->childItems()[0]->findChild<QQuickItem*>(RESOLUTION_SLIDER);
}

void Preset::Update()
{
    for(auto e : this->effects) {
        auto effect = preset->getEffect(e->getName());
        for(auto& p : effect->potentiometers) {
            p.second = e->ReadDial(p.first);
        }
        effect->state = e->ReadSwitch();
    }
    //preset->time_ms = editTime->property(SLIDER_VALUE).toDouble() * 1000;
    //preset->resolution = editResolution->property(SLIDER_VALUE).toInt();
}

void Preset::Show()
{
    editWindow->setVisible(true);
}

void Preset::Hide()
{
    editWindow->setVisible(false);
}

void Preset::Refresh()
{
    for(auto e : this->effects) {
        e->RefreshGui();
    }
    //editTime->setProperty(SLIDER_VALUE, QVariant::fromValue(preset->time_ms * 1000));
    //editResolution->setProperty(SLIDER_VALUE, QVariant::fromValue(preset->resolution * 1000));
}
