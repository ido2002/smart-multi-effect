#ifndef MENU_H
#define MENU_H

#include <QQuickItem>
#include <QString>
#include <functional>

class MenuItem
{
public:
    MenuItem(QString _name, std::function<int()> _func) {
        func = _func;
        name = _name;
    }

    int onClick() {
        return func();
    }

    QString getName() { return name; }

private:
    std::function<int()> func;
    QString name;
};

class Menu
{
public:
    Menu(QQuickItem* mainWindow);

    void left();
    void right();
    MenuItem* getCurrent(int offset = 0);

    void AddItem(MenuItem* item);

private:
    int index = 0;
    QQuickItem* main_window = nullptr;
    QQuickItem* drawer = nullptr;
    std::vector<MenuItem*> items;
};

#endif // MENU_H
