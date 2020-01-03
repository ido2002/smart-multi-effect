#include "soundprocessor.h"
#include "conf.h"
#include "FFT.h"
#include <iostream>
#include "fix_fft.h"
#include <cmath>

using namespace CONF::SOUNF_PROCCESSING;

SoundProcessor::SoundProcessor()
{
    using namespace CONF::SOUND_CARD;
    m_neuralNetwork = new NeuralNetwork(NEURAL_NETWORK_STRUCTURE);
    m_soundCard = new SoundCard(SAMPLE_BYTE_ORDER, CHANNEL_COUNT, CODEC,
                                SAMPLE_RATE, SAMPLE_SIZE, SAMPLE_FORMAT, BUFFER_SIZE);
    m_soundCard->SetOnBufferFill([&](int16_t* buffer, size_t bufferSize){
        InvokeOnBufferFill(buffer, bufferSize);
    }, BUFFER_FILL_SIZE);
}

void SoundProcessor::Start()
{
    m_soundCard->Start();
}

void SoundProcessor::Stop()
{
    m_soundCard->Stop();
}

void SoundProcessor::AddFunctionOnBufferFill(std::function<void (std::vector<float>, std::vector<float>)> func)
{
    m_functionsOnBufferFill.push_back(func);
}

void SoundProcessor::LoadSamples(std::string path)
{
    m_neuralNetwork->LoadData(path);
}

void SoundProcessor::AddSample(std::vector<float> FFT_output, std::list<Stroke::Note> notes)
{
    std::vector<float> expected(POSSIBLE_NOTES_COUNT);
    for(auto& it : expected) {
        it = 0.0f;
    }
    for(auto note : notes) {
        expected[static_cast<size_t>(note)] = 1.0f;
    }
    m_neuralNetwork->AddData(NetworkDataSet(FFT_output, expected));
}

void SoundProcessor::RecordSample(std::list<Stroke::Note> notes)
{
    bool beginning_state = m_soundCard->IsRunning();
    Start();

    //wait for high volume

    //while high volume: Add and wait RECORDING_WAIT_TIME_MILLISECOND
    AddSample(m_FFT_output_realTime, notes);

    if(beginning_state == false) {
        Stop();
    }
}

void SoundProcessor::Learn()
{
    m_neuralNetwork->Learn(1000);
    //std::cout << "learning times: 5000 + " << m_neuralNetwork->LearnUntilWork(2, 50000) << std::endl;
}

void SoundProcessor::LoadNetwork()
{

}

void SoundProcessor::InvokeOnBufferFill(int16_t *buffer, size_t bufferSize)
{
    FFT(buffer, bufferSize);
    m_notes_output_realTime = m_neuralNetwork->FeedForword(m_FFT_output_realTime);
    // notes to stroke...
    for(auto func : m_functionsOnBufferFill) {
        func(m_FFT_output_realTime, m_notes_output_realTime);
    }
}

void SoundProcessor::FFT(int16_t *buffer, size_t bufferSize)
{
#if 1
    int16_t* real = new int16_t[bufferSize];
    for(size_t i = 0; i < bufferSize; i++) {
        real[i] = buffer[i];
    }
    fix_fftr(real, std::log2(bufferSize), 1);
#else
    double* real = new double[bufferSize];
    double* imgn = new double[bufferSize];

    for(size_t i = 0; i < bufferSize; i++) {
        real[i] = buffer[i];
        imgn[i] = 0.0;
    }

    _FFT(1, static_cast<int>(std::log2(FFT_COUNT)), real, imgn);

#endif

    if(m_FFT_output_realTime.size() != FFT_COUNT) {
        m_FFT_output_realTime.resize(FFT_COUNT);
    }

    for(size_t i = 0; i < FFT_COUNT; i++) {
        m_FFT_output_realTime[i] = static_cast<float>(real[i]) / 0x10000; // ?
    }
}
