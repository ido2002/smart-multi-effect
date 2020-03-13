#include "guimanager.h"
#include "conf.h"
#include <iostream>
#include <thread>
#include <unistd.h>

#include <QQmlApplicationEngine>
#include <QQmlComponent>
#include <QCursor>

using namespace CONF;
using namespace GUI_PARAMETERS;

GUI_elements::GuiManager::GuiManager()
{
    engine.load(MAIN_WINDOW::MAIN_URL);

    //hide the cursor
    ///QGuiApplication::setOverrideCursor(QCursor(Qt::BlankCursor));

    //get main window, view area and buttons area
    mainWindow = (QQuickItem*)engine.rootObjects()[0];
    viewArea = mainWindow->findChild<QQuickItem*>(MAIN_WINDOW::MAIN_VIEW_AREA);
    buttonsArea = mainWindow->findChild<QQuickItem*>(MAIN_WINDOW::BUTTONS_AREA);

    //get buttons
    for(auto b : CUSTON_BUTTON::BUTTONS) {
        auto buttonItem = buttonsArea->findChild<QQuickItem*>(b)->findChild<QQuickItem*>(CUSTON_BUTTON::BUTTON);
        buttons.insert(std::pair<std::string, GuiButton*>(b.toStdString(), new GuiButton(buttonItem)));
        buttons[b.toStdString()]->SetText(b);
    }

    presetsPage = new PresetsWindow(&engine, viewArea);
    songsPage = new SongsWindow(&engine, viewArea);
    menu = new Menu(mainWindow);
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
    presetsPage->getCurrentPreset()->Hide();

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
        presetsPage->getCurrentPreset()->ShowActivePreset();
        break;

    case recordNote:
        break;
    case recordOctave:
        break;
    case train:
        break;
    case manage:
        break;
    }
}
