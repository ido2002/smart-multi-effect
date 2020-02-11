#ifndef SOUNDPROCESSOR_H
#define SOUNDPROCESSOR_H

#include "soundcard.h"
#include "stroke.h"
#include "neuralnetwork.h"

namespace sound_processing {
    class SoundProcessor
    {
    public:
        SoundProcessor();

        void Start();
        void Stop();

        void AddFunctionOnBufferFill(
                std::function<void(std::vector<float> fft, std::vector<float> notes, float volume)> func);

        void LoadSamples(std::string path);
        void AddSample(std::vector<float> FFT_output, std::vector<Stroke::Note> notes);
        void RecordSample(std::vector<Stroke::Note> notes);

        void Learn(size_t times = 500);

        void Save(bool data = true, bool network = true);
        void Load(bool data = true, bool network = true);

    private:
        void InvokeOnBufferFill(int16_t* buffer, size_t bufferSize);

        void FFT(int16_t* buffer, size_t bufferSize);
    private:
        SoundCard* m_soundCard = nullptr;
        NeuralNetwork* m_neuralNetwork = nullptr;

        std::vector<float> m_FFT_output_realTime;
        std::vector<float> m_notes_output_realTime;

        std::vector<double> m_FFT_re;
        std::vector<double> m_FFT_im;

        float avgVolume;

        std::list<std::function<void(
                std::vector<float> fft, std::vector<float> notes, float volume)>> m_functionsOnBufferFill;
    };
}
#endif // SOUNDPROCESSOR_H
