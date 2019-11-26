#ifndef GPIOCONTROL_H
#define GPIOCONTROL_H

#include <QObject>
#include <QString>
#include <QDir>
#include <QFile>

class GpioControl : public QObject
{
    Q_OBJECT
public:
    explicit GpioControl(uint ioPin, bool negativeLogic = false, QObject *parent = nullptr);
    ~GpioControl();

    void On();
    void Off();

signals:

public slots:

private:
    QFile* m_file = nullptr;
    bool m_negativeLogic = false;
};

#endif // GPIOCONTROL_H
