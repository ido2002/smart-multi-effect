#ifndef POTENTIOMETER_H
#define POTENTIOMETER_H

#include <QObject>

class Potentiometer : public QObject
{
    Q_OBJECT
public:
    explicit Potentiometer(QObject *parent = nullptr);

signals:

public slots:
};

#endif // POTENTIOMETER_H
