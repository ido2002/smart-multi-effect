#ifndef SOUNDCARD_H
#define SOUNDCARD_H

//done!

#include <QAudioDeviceInfo>
#include <QAudioInput>
#include <thread>
#include <functional>

class SoundCard
{
public:
    SoundCard(QAudioFormat::Endian byteOrder, int channelCount, QString codec,
              int sampleRate, int sampleSize, QAudioFormat::SampleType sampleType, qint64 bufferSize);

    ~SoundCard();

    void SetOnBufferFill(std::function<void(int16_t* buffer, size_t bufferSize)> onBufferFill, qint64 bufferFillSize);

    void Start();
    void Stop();

    bool IsRunning();

private:
    bool running = false;

    QIODevice* m_iodevice = nullptr;
    QAudioInput* m_audioInput = nullptr;
    QAudioFormat m_audioFormat;
    QAudioDeviceInfo m_audioInfo;

    qint64 m_bufferSize;
    int16_t* m_rawBuffer;
    int16_t* m_ch1_buffer;

    std::thread* m_readThread = nullptr;
    std::thread* m_onBufferFillThread = nullptr;
    std::function<void(int16_t* buffer, size_t bufferSize)> m_onBufferFill = nullptr;
    qint64 m_bufferFillSize = 0;
};

#endif // SOUNDCARD_H
