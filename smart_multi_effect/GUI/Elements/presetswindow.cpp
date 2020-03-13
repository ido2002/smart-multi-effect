#include "presetswindow.h"
#include "conf.h"

using namespace CONF::GUI_PARAMETERS::PAGES;

PresetsWindow::PresetsWindow(QQmlApplicationEngine *engine, QQuickItem *parent)
{
        //create component
        QQmlComponent comp(engine, parent);
        comp.loadUrl(PRESETS_URL);

        //add element
        window = qobject_cast<QQuickItem *>(comp.create());
        engine->setObjectOwnership(window, QQmlEngine::JavaScriptOwnership);
        window->setParentItem(parent);
        window->setVisible(false);
}

void PresetsWindow::Show()
{
    window->setVisible(true);
}

void PresetsWindow::Hide()
{
    window->setVisible(false);
}

void PresetsWindow::choose()
{

}

void PresetsWindow::left()
{
    index--;
    if(index < 0) index = frames.size() - 1;
    UpdateIndex();
}

void PresetsWindow::right()
{
    index++;
    if(index >= (int)frames.size()) index = 0;
    UpdateIndex();
}

void PresetsWindow::UpdateIndex()
{
    using namespace CONF::GUI_PARAMETERS::FRAMES;
    using namespace CONF::GUI_PARAMETERS::GENERAL_GUI_PROPERTIES_NAMES;

    window->childItems()[0]->findChild<QQuickItem*>(PRESET_NAME)->setProperty(LABLE_TEXT, frames[index]->name);
}

void PresetsWindow::AddFrame(PresetFrame *frame)
{
    frames.push_back(frame);
}

PresetFrame *PresetsWindow::getCurrentPreset()
{
    if(frames.size() == 0) {
        return nullptr;
    }
    return frames[index];
}
