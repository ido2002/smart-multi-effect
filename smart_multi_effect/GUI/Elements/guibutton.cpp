#include "guibutton.h"
#include "conf.h"

using namespace CONF::GUI_PARAMETERS;

GUI_elements::GuiButton::GuiButton(QQuickItem* button)
{
    buttonItem = button;
}

void GUI_elements::GuiButton::ClearFunctions()
{
    functions.clear();
}

void GUI_elements::GuiButton::AddFunction(std::function<void ()> func)
{
    functions.push_back(func);
}

void GUI_elements::GuiButton::Update()
{
    if(lastState == false && buttonItem->property("isPressed").toBool() == true) {
        lastState = true;
        for(auto func : functions) {
            func();
        }
    } else if(buttonItem->property("isPressed").toBool() == false) {
        lastState = false;
    }
}

void GUI_elements::GuiButton::SetText(QString text)
{
    buttonItem->findChild<QQuickItem*>(CUSTON_BUTTON::BUTTON_TEXT)->
            setProperty(GENERAL_GUI_PROPERTIES_NAMES::LABEL_TEXT, text);
}

QString GUI_elements::GuiButton::getText()
{
    return buttonItem->findChild<QQuickItem*>(CUSTON_BUTTON::BUTTON_TEXT)->
            property(GENERAL_GUI_PROPERTIES_NAMES::LABEL_TEXT).toString();
}

void GUI_elements::GuiButton::SetPressed(bool pressed)
{
    if(pressed) {
        buttonItem->setProperty(GENERAL_GUI_PROPERTIES_NAMES::COLOR, CUSTON_BUTTON::BUTTON_COLOR_PRESSED);
        buttonItem->setProperty(CUSTON_BUTTON::IS_PRESSED, true);
    } else {
        buttonItem->setProperty(GENERAL_GUI_PROPERTIES_NAMES::COLOR, CUSTON_BUTTON::BUTTON_COLOR);
        buttonItem->setProperty(CUSTON_BUTTON::IS_PRESSED, false);
    }
}

void GUI_elements::GuiButton::SetTextColor(QString color)
{
    buttonItem->findChild<QQuickItem*>(CUSTON_BUTTON::BUTTON_TEXT)->setProperty(GENERAL_GUI_PROPERTIES_NAMES::COLOR, color);
}

void GUI_elements::GuiButton::ResetTextColor()
{
    SetTextColor("#faf9f9");
}
