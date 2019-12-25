#ifndef SOUNDCARD_H
#define SOUNDCARD_H

#include <QObject>

class SoundCard : public QObject
{
    Q_OBJECT
public:
    explicit SoundCard(QObject *parent = nullptr);

signals:

public slots:
};

#endif // SOUNDCARD_H
