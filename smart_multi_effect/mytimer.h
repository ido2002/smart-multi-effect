#ifndef MYTIMER_H
#define MYTIMER_H

#include <QObject>
#include <QTimer>
#include <functional>
#include <list>

class MyTimer : public QObject
{
    Q_OBJECT
public:
    explicit MyTimer(QObject *parent = nullptr);

    void AddFunction(std::function<void()> func);

    void start(int ms);
    void start();
    void stop();
    bool isRunning();

signals:

public slots:
    void update();

private:
    QTimer* timer = nullptr;
    std::list<std::function<void()>> functionsOnUpdate;
    int ms = 0;
};

#endif // MYTIMER_H
