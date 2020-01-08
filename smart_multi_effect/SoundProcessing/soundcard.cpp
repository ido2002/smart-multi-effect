#include "soundcard.h"
#include <qdebug.h>


SoundCard::SoundCard(QAudioFormat::Endian byteOrder, int channelCount, QString codec,
                     int sampleRate, int sampleSize, QAudioFormat::SampleType sampleType, qint64 bufferSize)
{
    m_bufferSize = bufferSize;

    m_audioFormat.setByteOrder(byteOrder);
    m_audioFormat.setChannelCount(channelCount);
    m_audioFormat.setCodec(codec);
    m_audioFormat.setSampleRate(sampleRate);
    m_audioFormat.setSampleSize(sampleSize);
    m_audioFormat.setSampleType(sampleType);

    m_audioInfo = QAudioDeviceInfo::defaultInputDevice();
    m_audioFormat = m_audioInfo.nearestFormat(m_audioFormat);

    qDebug() << "my device: " << m_audioInfo.deviceName() << "---------------------------------";
    qDebug() << "   rate " << m_audioFormat.sampleRate();
    qDebug() << "   size " << m_audioFormat.sampleSize();
    qDebug() << "   byte order " << m_audioFormat.byteOrder();
    qDebug() << "   type " << m_audioFormat.sampleType();
    qDebug() << "   ch count " << m_audioFormat.channelCount();

    m_audioInput = new QAudioInput(m_audioInfo, m_audioFormat);

    m_audioInput->setBufferSize(static_cast<int>(m_bufferSize * 4));
    m_rawBuffer = new int16_t[m_bufferSize * 2/*chanels*/];
    m_ch1_buffer = new int16_t[m_bufferSize];
}

SoundCard::~SoundCard()
{
    Stop();
    delete m_audioInput;
}

void SoundCard::SetOnBufferFill(std::function<void (int16_t *, size_t)> onBufferFill, qint64 bufferFillSize)
{
    m_bufferFillSize = bufferFillSize;
    m_onBufferFill = onBufferFill;
    if(m_bufferFillSize > m_bufferSize) {
        qDebug() << "warning: bufferFillSize > bufferSize";
    }
}

void SoundCard::Start()
{
    running = true;
    if(m_readThread != nullptr) {
        return;
    }

    //open thread
    m_readThread = new std::thread([&](){
        //setup:
        qint64 bufferPos = 0;
        qint64 lastBufferPos = 0;
        char* buffer = reinterpret_cast<char*>(m_rawBuffer);
        qint64 sampleSize = static_cast<qint64>(sizeof (int16_t)) *
                static_cast<qint64>(m_audioFormat.channelCount());
        qint64 written = 0;

        m_iodevice = m_audioInput->start();

        while(true) {
            //read to buffer
            bufferPos += (m_iodevice->read(&buffer[bufferPos * sampleSize], (m_bufferSize-bufferPos) * sampleSize)) / sampleSize;

            auto temp = bufferPos - lastBufferPos;
            while(temp < 0) {
                temp += m_bufferSize;
            }
            written += temp;

            lastBufferPos = bufferPos;

            if(bufferPos >= m_bufferSize) {
                bufferPos = 0;
            }

            //onBufferFill
            if(written >= m_bufferFillSize) {
                written -= m_bufferFillSize;

                //wait for last thread
                if(m_onBufferFillThread != nullptr) {
                    m_onBufferFillThread->join();
                    delete m_onBufferFillThread;
                }

                //read ch1 from the buffer
                for(qint64 i = 0; i < m_bufferSize; i++) {
                    m_ch1_buffer[i] = m_rawBuffer[i*m_audioFormat.channelCount()];
                }

                //open thread
                m_onBufferFillThread = new std::thread([&](){
                    if(m_onBufferFill != nullptr)
                        m_onBufferFill(m_ch1_buffer, static_cast<size_t>(m_bufferSize));
                });
            }
        }
    });
}

void SoundCard::Stop()
{
    running = false;
    delete m_readThread;
    m_readThread = nullptr;
}

bool SoundCard::IsRunning()
{
    return running;
}
