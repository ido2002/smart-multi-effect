#include "presetswindow.h"
#include "conf.h"
#include "jsonreader.h"

using namespace CONF::GUI_PARAMETERS::PRESETS_PAGE;
using namespace CONF::PRESETS_AND_SONGS_DATA;

PresetsWindow::PresetsWindow(QQmlApplicationEngine *engine, QQuickItem *parent)
{
    this->engine = engine;
    this->parent = parent;
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
    using namespace CONF::GUI_PARAMETERS::GENERAL_GUI_PROPERTIES_NAMES;

    window->findChild<QQuickItem*>(PRESET_NAME)->setProperty(LABEL_TEXT, presetWindows[index]->getName());
}

void PresetsWindow::SaveAll()
{
    presetsPath.clear();
    for(auto pw : presetWindows) {
        pw->getP1()->Save();
        pw->getP2()->Save();
        pw->getP3()->Save();
        pw->getP4()->Save();
        QVariantMap pwMap;
        pwMap.insert("name", pw->getName());
        pwMap.insert("presets", QVariantList({
                pw->getP1()->getName(),
                pw->getP2()->getName(),
                pw->getP3()->getName(),
                pw->getP4()->getName()
                }));
        char str[4] = "000";
        sprintf(str, "%03d", presetsPath.size());
        presetsPath.insert(QString::fromStdString(str), pwMap);
    }
    JsonReader::writeJsonFile(presetsPath, PRESETS_SAVE_DIRECTORY + PRESETS_FILE);
}

bool PresetsWindow::LoadAll()
{
    JsonReader::readJsonFile(PRESETS_SAVE_DIRECTORY + PRESETS_FILE, presetsPath);
    if(presetsPath.size() == 0) {
        return false;
    }
    int index = 0;
    presetWindows.clear();
    for(auto s : presetsPath) {
        QVariantMap set = s.toMap();
        presetWindows.push_back(new PresetWindow(set.find("name")->toString()));
        presetWindows[index]->setP1(new Preset(set.find("name")->toString(), set.find("presets")->toStringList()[0], engine, parent));
        presetWindows[index]->setP2(new Preset(set.find("name")->toString(), set.find("presets")->toStringList()[1], engine, parent));
        presetWindows[index]->setP3(new Preset(set.find("name")->toString(), set.find("presets")->toStringList()[2], engine, parent));
        presetWindows[index]->setP4(new Preset(set.find("name")->toString(), set.find("presets")->toStringList()[3], engine, parent));
        index++;
    }
    return true;
}

std::map<QString, std::vector<QString>> PresetsWindow::GenPresetsMap()
{
    using pair = std::pair<QString, std::vector<QString>>;

    for(auto pw : presetWindows) {
        presetsMap.insert(pair(pw->getName(), {
                            pw->getP1()->getName(),
                            pw->getP2()->getName(),
                            pw->getP3()->getName(),
                            pw->getP4()->getName() }));
    }

    return presetsMap;
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

hardware_ctrl::Preset *PresetsWindow::getPreset(QString set, QString name)
{
    for(auto pw : presetWindows) {
        if(pw->getName() == set) {
            if(pw->getP1()->getName() == name) {
                return pw->getP1()->getPreset();
            }
            if(pw->getP2()->getName() == name) {
                return pw->getP2()->getPreset();
            }
            if(pw->getP3()->getName() == name) {
                return pw->getP3()->getPreset();
            }
            if(pw->getP4()->getName() == name) {
                return pw->getP4()->getPreset();
            }
        }
    }
    return nullptr;
}
