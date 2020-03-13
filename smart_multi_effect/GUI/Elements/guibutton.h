#ifndef GUIBUTTON_H
#define GUIBUTTON_H

#include <QQuickItem>
#include <QtQuick>
#include <functional>
#include <list>

namespace GUI_elements {
    class GuiButton
    {
    public:
        GuiButton(QQuickItem* button);

        void ClearFunctions();
        void AddFunction(std::function<void()> func);
        void Update();
        void SetText(QString text);
        QString getText();
        void SetPressed(bool pressed);

        void SetTextColor(QString color);
        void ResetTextColor();

    private:
        std::list<std::function<void()>> functions;
        QQuickItem* buttonItem;
        bool lastState = false;
    };
}


#endif // GUIBUTTON_H
