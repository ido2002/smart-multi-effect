#ifndef POTENTIOMETER_H
#define POTENTIOMETER_H

#include <QObject>
#include "gpiocontrol.h"

class Potentiometer : public QObject
{
    Q_OBJECT
public:
    explicit Potentiometer(uint ioNumber, bool NegativeLogic = false, QObject *parent = nullptr);
    ~Potentiometer();

    void SetTarget(uint target);
    uint GetValue();
    void CS(bool on_off);
    bool Check(bool increceUp);

signals:

public slots:

private:
    GpioControl* m_chipSelectPin = nullptr;
    uint m_currentValue = 0;
    uint m_targetValue = 0;
};

#endif // POTENTIOMETER_H
