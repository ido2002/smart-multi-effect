#ifndef LOADINGPAGE_H
#define LOADINGPAGE_H

#include <QQuickItem>
#include <QQmlApplicationEngine>

class LoadingPage
{
public:
    LoadingPage(QQmlApplicationEngine *engine, QQuickItem *parent);

    void Show();
    void Hide();

private:
    QQuickItem* window;
};

#endif // LOADINGPAGE_H
