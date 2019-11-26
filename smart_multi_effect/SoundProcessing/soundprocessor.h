#ifndef SOUNDPROCESSOR_H
#define SOUNDPROCESSOR_H

#include <QObject>

class SoundProcessor : public QObject
{
    Q_OBJECT
public:
    explicit SoundProcessor(QObject *parent = nullptr);

signals:

public slots:
};

#endif // SOUNDPROCESSOR_H
