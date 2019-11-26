#ifndef RELAY_H
#define RELAY_H

#include <QObject>

class Relay : public QObject
{
    Q_OBJECT
public:
    explicit Relay(QObject *parent = nullptr);

signals:

public slots:
};

#endif // RELAY_H
