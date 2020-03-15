#ifndef SOUNDPROCESSOR_H
#define SOUNDPROCESSOR_H

#include "soundcard.h"
#include "stroke.h"
#include "neuralnetwork.h"
#include "noterecognition.h"

namespace sound_processing {
    class SoundProcessor
    {
    public:
        SoundProcessor();
        ~SoundProcessor();

        void Start();
        void Stop();

        void AddFunctionOnBufferFill(
                std::function<void(int16_t* buffer, size_t bufferSize, Stroke stroke)> func);

        void RecordNoteSample(std::vector<Stroke::Note> notes);
        void RecordOctaveSample(std::vector<float> octaves);

        void Learn(size_t notes = 500, size_t octaves = 500);

        NoteRecognition& getNoteRecognition() const { return *m_noteRecognition; }

    private:
        void InvokeOnBufferFill(int16_t* buffer, size_t bufferSize);

    private:
        SoundCard* m_soundCard = nullptr;
        NoteRecognition* m_noteRecognition = nullptr;

        std::list<std::function<void(
                int16_t* buffer, size_t bufferSize, Stroke stroke)>> m_functionsOnBufferFill;

        Stroke* LastStroke = nullptr;
        std::vector<uint16_t> Buffer_rt;
    };
}
#endif // SOUNDPROCESSOR_H
