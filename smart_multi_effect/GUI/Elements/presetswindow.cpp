#include "presetswindow.h"
#include "conf.h"

using namespace CONF::GUI_PARAMETERS::PRESETS_PAGE;

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
    if(index < 0) index = presetWindows.size() - 1;
    UpdateIndex();
}

void PresetsWindow::right()
{
    index++;
    if(index >= (int)presetWindows.size()) index = 0;
    UpdateIndex();
}

void PresetsWindow::UpdateIndex()
{
    using namespace CONF::GUI_PARAMETERS::SONG_FRAME;
    using namespace CONF::GUI_PARAMETERS::GENERAL_GUI_PROPERTIES_NAMES;

    window->findChild<QQuickItem*>(PRESET_NAME)->setProperty(LABLE_TEXT, presetWindows[index]->getName());
}

void PresetsWindow::AddPresetWindow(PresetWindow *presetWindow)
{
    presetWindows.push_back(presetWindow);
}

PresetWindow *PresetsWindow::getCurrentPreset()
{
    if(presetWindows.size() == 0) {
        return nullptr;
    }
    return presetWindows[index];
}
