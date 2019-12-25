#ifndef GPIOCONTROL_H
#define GPIOCONTROL_H

#include <QObject>
#include <QString>
#include <QDir>
#include <QFile>
#include <iostream>
#include <unistd.h>

class GpioControl : public QObject
{
    Q_OBJECT
public:
    explicit GpioControl(uint ioPin, bool negativeLogic = false, bool isOut = true, QObject *parent = nullptr);
    ~GpioControl();

    void On();
    void Off();
    bool Read();
    void Tick(uint time_usec, bool tickOn = true);

signals:
    void ValueChanged(bool value);
public slots:

private:
    QFile* m_file = nullptr;
    bool m_negativeLogic = false;
    bool m_isOut = true;
    uint m_ioPin = 0;
    bool m_current = false;
};

#endif // GPIOCONTROL_H
