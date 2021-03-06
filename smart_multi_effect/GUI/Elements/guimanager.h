#ifndef GUIMANAGER_H
#define GUIMANAGER_H

#include <QQuickItem>
#include <QFlags>
#include <QFlag>
#include "guibutton.h"
#include "effect_gui.h"
#include "presetswindow.h"
#include "autoswitchsetswindow.h"
#include "menu.h"
#include "recordnote.h"
#include "recordoctave.h"
#include "train.h"
#include "loadingpage.h"

namespace GUI_elements {
    class GuiManager
    {
    public:
        enum ViewAreaContent { nothing, songs, presets, song, preset, recordNote, recordOctave, train, manage, loading};
    public:
        GuiManager();

        GuiButton* getButtonByName(std::string name);

        void UpdateButtons();

        void SetViewAreaTo(ViewAreaContent content);

        PresetsWindow* getPresetsWindow() { return presetsPage; }
        AutoSwitchSetsWindow* getSongsWindow() { return autoSwitchSetsWindow; }
        Menu* getMenu() { return menu; }
        RecordNotePage* getRecordNotePage() { return recordNotePage; }
        RecordOctavePage* getRecordOctavePage() { return recordOctavePage; }
        TrainingPage* getTrainingPage() { return trainingPage; }

        QQmlApplicationEngine* getEngine() { return &engine; }
        QQuickItem* &getViewArea() { return viewArea; }

    private:
        QQmlApplicationEngine engine;

        QQuickItem* mainWindow = nullptr;
        QQuickItem* viewArea = nullptr;

        QQuickItem* buttonsArea = nullptr;
        std::map<std::string, GuiButton*> buttons;

        AutoSwitchSetsWindow* autoSwitchSetsWindow = nullptr;
        PresetsWindow* presetsPage = nullptr;
        Menu* menu = nullptr;
        RecordNotePage* recordNotePage = nullptr;
        RecordOctavePage* recordOctavePage = nullptr;
        TrainingPage* trainingPage = nullptr;
        LoadingPage* loadingPage = nullptr;
    };
}
#endif // GUIMANAGER_H
