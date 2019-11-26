#ifndef EFFECT_H
#define EFFECT_H

#include <QObject>

class Effect : public QObject
{
    Q_OBJECT
public:
    explicit Effect(QObject *parent = nullptr);

signals:

public slots:
};

#endif // EFFECT_H
