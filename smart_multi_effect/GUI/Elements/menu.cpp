#include "menu.h"
#include <iostream>

Menu::Menu(QQuickItem *mainWindow)
{
    main_window = mainWindow;
    drawer = main_window->findChild<QQuickItem*>("drawer");
}

void Menu::left()
{
    index--;
    if(index < 0) index = items.size() - 1;
}

void Menu::right()
{
    index++;
    if(index >= (int)items.size()) index = 0;
}

MenuItem *Menu::getCurrent(int offset)
{
    return items[(index + offset)%items.size()];
}

void Menu::AddItem(MenuItem* item)
{
    items.push_back(item);
}
