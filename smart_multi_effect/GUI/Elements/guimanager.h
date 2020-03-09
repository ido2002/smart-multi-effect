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

    private:
        QQuickItem* mainWindow = nullptr;
        QQuickItem* viewArea = nullptr;
        QQuickItem* songsPage = nullptr;
        QQuickItem* presetsPage = nullptr;
        QQuickItem* buttonsArea = nullptr;
        std::map<std::string, GuiButton*> buttons;
        std::map<std::string, SongFrame*> songsFrames;
        std::map<std::string, PresetFrame*> presetsFrames;
    };
}
#endif // GUIMANAGER_H
