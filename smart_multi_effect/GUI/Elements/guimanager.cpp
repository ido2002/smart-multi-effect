#include "guimanager.h"
#include "conf.h"
#include <iostream>
#include <thread>
#include <unistd.h>

#include <QQmlApplicationEngine>
#include <QQmlComponent>
#include <QCursor>

#define RASPBERRY_PI

using namespace CONF;
using namespace GUI_PARAMETERS;

GUI_elements::GuiManager::GuiManager()
{
    engine.load(MAIN_WINDOW::MAIN_URL);

    //hide the cursor
#ifdef RASPBERRY_PI
    QGuiApplication::setOverrideCursor(QCursor(Qt::BlankCursor));
#endif

    //get main window, view area and buttons area
    mainWindow = (QQuickItem*)engine.rootObjects()[0];
    viewArea = mainWindow->findChild<QQuickItem*>(MAIN_WINDOW::MAIN_VIEW_AREA);
    buttonsArea = mainWindow->findChild<QQuickItem*>(MAIN_WINDOW::BUTTONS_AREA);

#ifndef RASPBERRY_PI
    mainWindow->setProperty("visibility", "Windowed");
#else
    mainWindow->setProperty("visibility", "FullScreen");
#endif

    //get buttons
    for(auto b : CUSTON_BUTTON::BUTTONS) {
        auto buttonItem = buttonsArea->findChild<QQuickItem*>(b)->findChild<QQuickItem*>(CUSTON_BUTTON::BUTTON);
        buttons.insert(std::pair<std::string, GuiButton*>(b.toStdString(), new GuiButton(buttonItem)));
        buttons[b.toStdString()]->SetText(b);
    }

    presetsPage = new PresetsWindow(&engine, viewArea);
    autoSwitchSetsWindow = new AutoSwitchSetsWindow(&engine, viewArea);
    menu = new Menu(mainWindow);
    recordNotePage = new RecordNotePage(&engine, viewArea);
    recordOctavePage = new RecordOctavePage(&engine, viewArea);
    trainingPage = new TrainingPage(&engine, viewArea);
    loadingPage = new LoadingPage(&engine, viewArea);
}

GUI_elements::GuiButton *GUI_elements::GuiManager::getButtonByName(std::string name)
{
    return buttons.find(name)->second;
}

void GUI_elements::GuiManager::UpdateButtons()
{
    for(auto b : buttons) {
        b.second->Update();
    }
}

void GUI_elements::GuiManager::SetViewAreaTo(GUI_elements::GuiManager::ViewAreaContent content)
{
    presetsPage->Hide();
    autoSwitchSetsWindow->Hide();
    if(presetsPage->getCurrentPreset()) {
        presetsPage->getCurrentPreset()->Hide();
    }
    if(autoSwitchSetsWindow->getCurrentSet()) {
        autoSwitchSetsWindow->getCurrentSet()->Hide();
    }
    recordNotePage->Hide();
    recordOctavePage->Hide();
    trainingPage->Hide();
    loadingPage->Hide();

    switch(content) {
    case nothing:
        break;
    case songs:
        autoSwitchSetsWindow->Show();
        break;
    case presets:
        presetsPage->UpdateIndex();
        presetsPage->Show();
        break;
    case song:
        if(autoSwitchSetsWindow->getCurrentSet()) {
            autoSwitchSetsWindow->getCurrentSet()->Show();
        }
        break;
    case preset:
        presetsPage->getCurrentPreset()->ShowActivePreset();
        break;

    case recordNote:
        recordNotePage->Show();
        break;
    case recordOctave:
        recordOctavePage->Show();
        break;
    case train:
        trainingPage->Show();
        break;
    case manage:
        break;
    case loading:
        loadingPage->Show();
        break;
    }
}
