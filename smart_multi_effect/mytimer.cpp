#include "mytimer.h"

MyTimer::MyTimer(QObject *parent) : QObject(parent)
{
    timer = new QTimer;
    connect(timer, &QTimer::timeout, this, &MyTimer::update);
}

void MyTimer::AddFunction(std::function<void ()> func)
{
    functionsOnUpdate.push_back(func);
}

void MyTimer::start(int ms)
{
    this->ms = ms;
    if(!timer->isActive())
        timer->start(ms);
}

void MyTimer::start()
{
    if(!timer->isActive())
        timer->start(ms);
}

void MyTimer::stop()
{
    if(timer->isActive())
        timer->stop();
}

bool MyTimer::isRunning()
{
    return timer->isActive();
}

void MyTimer::update()
{
    for(auto func : functionsOnUpdate) {
        func();
    }
}
