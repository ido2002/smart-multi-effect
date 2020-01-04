#include "soundprocessor.h"
#include "conf.h"
#include "FFT.h"
#include <iostream>
#include <cmath>

const float SHORT_K_f = (100.0f / ((long)1 << 30));

using namespace CONF::SOUND_PROCCESSING;

SoundProcessor::SoundProcessor()
{
    using namespace CONF::SOUND_CARD;
    m_neuralNetwork = new NeuralNetwork(NEURAL_NETWORK_STRUCTURE);
    m_soundCard = new SoundCard(SAMPLE_BYTE_ORDER, CHANNEL_COUNT, CODEC,
                                SAMPLE_RATE, SAMPLE_SIZE, SAMPLE_FORMAT, BUFFER_SIZE);
    m_soundCard->SetOnBufferFill([&](int16_t* buffer, size_t bufferSize){
        InvokeOnBufferFill(buffer, bufferSize);
    }, BUFFER_FILL_SIZE);

    m_FFT_output_realTime.resize(FFT_COUNT);
    m_FFT_re.resize(BUFFER_SIZE);
    m_FFT_im.resize(BUFFER_SIZE);
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
    int learned = 0;
    int max = 1000;
    int jump = 10;
    for(int i = 0; i <= max; i += jump) {
        m_neuralNetwork->Learn(i - learned);
        learned = i;
        std::cout << (learned * 100 / max) << "% learned[" << max << "]: " << learned << std::endl;
    }
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
    using namespace CONF::SOUND_CARD;
    // check buffer size
    if(bufferSize < BUFFER_SIZE) {
        std::cout << "error" << std::endl;
        return;
    }

    // set up re and im
    for(size_t i = 0; i < BUFFER_SIZE; i++) {
        m_FFT_re[i] = buffer[i];
        m_FFT_im[i] = 0.0;
    }

    // performing FFT
    _FFT(1, static_cast<int>(log2(FFT_COUNT)), &m_FFT_re[0], &m_FFT_im[0]);

    // calculating results
    for(size_t i = 0; i < FFT_COUNT; i++) {
        float re = m_FFT_re[i];
        float im = m_FFT_im[i];
        m_FFT_output_realTime[i] = sqrt((re * re + im * im) * SHORT_K_f);
    }
}
