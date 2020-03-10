#ifndef GUIMANAGER_H
#define GUIMANAGER_H

#include <QQuickItem>
#include <QFlags>
#include <QFlag>
#include "guibutton.h"
#include "effect_gui.h"
#include "songframe.h"
#include "presetframe.h"

namespace GUI_elements {
    class GuiManager
    {
    public:
        GuiManager();

        GuiButton* getButtonByName(std::string name);

        void UpdateButtons();

    public:
        QQmlApplicationEngine engine;

        QQuickItem* mainWindow = nullptr;
        QQuickItem* viewArea = nullptr;

        QQuickItem* buttonsArea = nullptr;
        std::map<std::string, GuiButton*> buttons;

        QQuickItem* songsPage = nullptr;
        std::map<std::string, SongFrame*> songsFrames;

        QQuickItem* presetsPage = nullptr;
        std::map<std::string, PresetFrame*> presetsFrames;

        QQuickItem* editArea = nullptr;
        std::map<std::string, Effect_gui*> effects;
    };
}
#endif // GUIMANAGER_H
