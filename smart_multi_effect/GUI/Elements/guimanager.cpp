#include "guimanager.h"
#include "conf.h"
#include <iostream>
#include <thread>
#include <unistd.h>

#include <QQmlApplicationEngine>
#include <QQmlComponent>

using namespace CONF;
using namespace GUI_PARAMETERS;

GUI_elements::GuiManager::GuiManager()
{
    engine.load(PAGES::MAIN_URL);

    //get main window, view area and buttons area
    mainWindow = (QQuickItem*)engine.rootObjects()[0];
    viewArea = mainWindow->findChild<QQuickItem*>(PAGES::MAIN_VIEW_AREA);
    buttonsArea = mainWindow->findChild<QQuickItem*>(PAGES::BUTTONS_AREA);

    //get buttons
    for(auto b : CUSTON_BUTTON::BUTTONS) {
        auto buttonItem = buttonsArea->findChild<QQuickItem*>(b)->findChild<QQuickItem*>(CUSTON_BUTTON::BUTTON);
        buttons.insert(std::pair<std::string, GuiButton*>(b.toStdString(), new GuiButton(buttonItem)));
        buttons[b.toStdString()]->SetText(b);
    }

    presetsPage = new PresetsWindow(&engine, viewArea);
    songsPage = new SongsWindow(&engine, viewArea);
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
    songsPage->Hide();

    switch(content) {
    case nothing:
        break;
    case songs:
        songsPage->Show();
        break;
    case presets:
        presetsPage->UpdateIndex();
        presetsPage->Show();
        break;
    case song:
        break;
    case preset:
        break;
    }
}
