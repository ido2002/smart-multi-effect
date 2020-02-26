#include "noterecognition.h"
#include "FFT.h"


sound_processing::NoteRecognition::NoteRecognition()
{

}

sound_processing::Stroke sound_processing::NoteRecognition::BufferToStroke(int16_t *buffer, size_t bufferSize)
{
    TimePoint start = std::chrono::steady_clock::now();
    std::vector<double> m_FFT_re(bufferSize);
    std::vector<double> m_FFT_im(bufferSize, 0);
    for(size_t i = 0; i < bufferSize; i++) {
        m_FFT_re[i] = buffer[i];
    }
    _FFT(1, static_cast<int>(log2(bufferSize)), &m_FFT_re[0], &m_FFT_im[0]);
    std::list<Stroke::Note> notes;
    Stroke::VolumeLevel vol = Stroke::VolumeLevel::silence;
    Stroke stroke(start, notes, vol);
    return stroke;
}
