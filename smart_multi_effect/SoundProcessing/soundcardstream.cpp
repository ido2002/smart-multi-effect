#include "soundcardstream.h"

SoundCardStrem::SoundCardStrem(size_t bufferSize, int channelCount, QObject *parent) : QIODevice(parent)
{
    m_bufferSize = bufferSize;
    m_channelCount = channelCount;
    m_buffer = new T[m_bufferSize];
}

qint64 SoundCardStrem::writeData(const char *data, qint64 len)
{
    qint64 writen = 0;

//    for(size_t i = 0; i + sizeof(T) <= static_cast<size_t>(len); i += sizeof(T) * m_channelCount) {
//        m_buffer[m_currentWriteIndex] = reinterpret_cast<const T*>(data)[i];
//        writen += sizeof(T);
//        m_currentWriteIndex++;
//        if(m_currentWriteIndex >= m_bufferSize) {
//            m_currentWriteIndex = 0;
//        }
//    }

    return writen;
}

qint64 SoundCardStrem::readData(char *data, qint64 maxlen)
{
    qint64 writen = 0;

//    for(size_t i = 0; i + sizeof(T) <= static_cast<size_t>(maxlen); i += sizeof(T)) {
//        reinterpret_cast<T*>(data)[i] = m_buffer[m_currentReadIndex];
//        writen += sizeof(T);
//        m_currentReadIndex++;
//        if(m_currentReadIndex >= m_bufferSize) {
//            m_currentReadIndex = 0;
//        }
//    }

    return writen;
}
