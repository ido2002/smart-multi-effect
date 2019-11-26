#ifndef RIFF_H
#define RIFF_H

#include <QObject>

class Riff : public QObject
{
    Q_OBJECT
public:
    explicit Riff(QObject *parent = nullptr);

signals:

public slots:
};

#endif // RIFF_H
