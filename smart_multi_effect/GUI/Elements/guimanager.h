#ifndef GUIMANAGER_H
#define GUIMANAGER_H

#include <QQuickItem>
#include <QFlags>
#include <QFlag>
#include "guibutton.h"
#include "effect_gui.h"
#include "presetswindow.h"
#include "songswindow.h"

namespace GUI_elements {
    class GuiManager
    {
    public:
        enum ViewAreaContent { nothing, songs, presets, song, preset};
    public:
        GuiManager();

        GuiButton* getButtonByName(std::string name);

        void UpdateButtons();

        void SetViewAreaTo(ViewAreaContent content);

        PresetsWindow* getPresetsWindow() { return presetsPage; }
        SongsWindow* getSongsWindow() { return songsPage; }

    private:
        QQmlApplicationEngine engine;

        QQuickItem* mainWindow = nullptr;
        QQuickItem* viewArea = nullptr;

        QQuickItem* buttonsArea = nullptr;
        std::map<std::string, GuiButton*> buttons;

        SongsWindow* songsPage = nullptr;

        PresetsWindow* presetsPage = nullptr;

        QQuickItem* editArea = nullptr;
        std::map<std::string, Effect_gui*> effects;
    };
}
#endif // GUIMANAGER_H
