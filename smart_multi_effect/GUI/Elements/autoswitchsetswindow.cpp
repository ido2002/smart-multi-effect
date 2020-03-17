#include "autoswitchsetswindow.h"
#include "conf.h"

using namespace CONF::GUI_PARAMETERS::SONGS_PAGE;


AutoSwitchSetsWindow::AutoSwitchSetsWindow(QQmlApplicationEngine *engine, QQuickItem *parent)
{
    //create component
    QQmlComponent comp(engine, parent);
    comp.loadUrl(SONGS_URL);

    //add element
    window = qobject_cast<QQuickItem *>(comp.create());
    engine->setObjectOwnership(window, QQmlEngine::JavaScriptOwnership);
    window->setParentItem(parent);
    window->setVisible(false);
}

void AutoSwitchSetsWindow::UpdatePresets(PresetsWindow *presets)
{
    for(auto set : sets) {
        set->UpdatePresets(presets);
    }
}

void AutoSwitchSetsWindow::Show()
{
    window->setVisible(true);
    UpdateIndex();
}

void AutoSwitchSetsWindow::Hide()
{
    window->setVisible(false);
}

void AutoSwitchSetsWindow::choose()
{

}

void AutoSwitchSetsWindow::left()
{
    index--;
    if(index < 0) index = sets.size() - 1;
    UpdateIndex();
}

void AutoSwitchSetsWindow::right()
{
    index++;
    if(index >= (int)sets.size()) index = 0;
    UpdateIndex();
}

void AutoSwitchSetsWindow::UpdateIndex()
{
    using namespace CONF::GUI_PARAMETERS::GENERAL_GUI_PROPERTIES_NAMES;

    window->findChild<QQuickItem*>(SONG_NAME)->setProperty(LABEL_TEXT, sets[index]->getName());
}

void AutoSwitchSetsWindow::AddSet(AutoSwitchSetWindowEdit *set)
{
    sets.push_back(set);
}

AutoSwitchSetWindowEdit *AutoSwitchSetsWindow::getCurrentSet()
{
    if(sets.size() == 0) {
        return nullptr;
    }
    return sets[index];
}
