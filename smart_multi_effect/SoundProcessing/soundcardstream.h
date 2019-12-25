#ifndef SOUNDCARDSTREAM_H
#define SOUNDCARDSTREAM_H

#include <QObject>
#include <QIODevice>

class SoundCardStrem : public QIODevice
{
    Q_OBJECT
private:
    typedef uint16_t T;

public:
    explicit SoundCardStrem(std::size_t bufferSize, int channelCount, QObject *parent = nullptr);

    qint64 writeData(const char *data, qint64 len) override;

    qint64 readData(char *data, qint64 maxlen) override;

signals:

public slots:

private:
    T* m_buffer = nullptr;
    size_t m_bufferSize = 0;
    int m_channelCount = 0;
    size_t m_currentReadIndex = 0;
    size_t m_currentWriteIndex = 0;
};

#endif // SOUNDCARDSTREAM_H
