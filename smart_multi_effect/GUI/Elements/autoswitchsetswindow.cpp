#include "autoswitchsetswindow.h"
#include "conf.h"
#include "jsonreader.h"

using namespace CONF::GUI_PARAMETERS::SONGS_PAGE;


AutoSwitchSetsWindow::AutoSwitchSetsWindow(QQmlApplicationEngine *engine, QQuickItem *parent)
{
    this->engine = engine;
    this->parent = parent;

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

void AutoSwitchSetsWindow::SaveAll()
{
    using namespace CONF::PRESETS_AND_SONGS_DATA;
    setsPath.clear();
    for(auto set : sets) {
        QVariantMap setMap = set->GenMap();
        QString path = SONGS_SAVE_DIRECTORY + set->getName() + SONG_FILE_ENDING;
        JsonReader::writeJsonFile(setMap, path);

        char str[4] = "000";
        sprintf(str, "%03d", setsPath.size());
        setsPath.insert(QString::fromStdString(str), path);
    }
    JsonReader::writeJsonFile(setsPath, SONGS_SAVE_DIRECTORY + SONGS_FILE);
}

bool AutoSwitchSetsWindow::LoadAll()
{
    using namespace CONF::PRESETS_AND_SONGS_DATA;
    JsonReader::readJsonFile(SONGS_SAVE_DIRECTORY + SONGS_FILE, setsPath);

    if(setsPath.size() == 0) {
        return false;
    }

    sets.clear();
    for(auto s : setsPath) {
        QString path = s.toString();
        QVariantMap setMap;
        JsonReader::readJsonFile(path, setMap);
        sets.push_back(new AutoSwitchSetWindowEdit(setMap, engine, parent));
    }
    return true;
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
