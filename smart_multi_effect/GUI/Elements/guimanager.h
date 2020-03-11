#ifndef GUIMANAGER_H
#define GUIMANAGER_H

#include <QQuickItem>
#include <QFlags>
#include <QFlag>
#include "guibutton.h"
#include "effect_gui.h"
#include "presetswindow.h"
#include "songswindow.h"
#include "menu.h"

namespace GUI_elements {
    class GuiManager
    {
    public:
        enum ViewAreaContent { nothing, songs, presets, song, preset, recordNote, recordOctave, train, manage};
    public:
        GuiManager();

        GuiButton* getButtonByName(std::string name);

        void UpdateButtons();

        void SetViewAreaTo(ViewAreaContent content);

        PresetsWindow* getPresetsWindow() { return presetsPage; }
        SongsWindow* getSongsWindow() { return songsPage; }
        Menu* getMenu() { return menu; }

    private:
        QQmlApplicationEngine engine;

        QQuickItem* mainWindow = nullptr;
        QQuickItem* viewArea = nullptr;

        QQuickItem* buttonsArea = nullptr;
        std::map<std::string, GuiButton*> buttons;

        SongsWindow* songsPage = nullptr;

        PresetsWindow* presetsPage = nullptr;

        Menu* menu = nullptr;
    };
}
#endif // GUIMANAGER_H
