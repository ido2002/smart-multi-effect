#include "soundprocessor.h"
#include "conf.h"
#include "FFT.h"
#include <iostream>
#include <cmath>
#include <unistd.h>

#define K * 1000

const float MAX_SHORT = 1 << 15;

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

void SoundProcessor::AddFunctionOnBufferFill(std::function<void (std::vector<float>, std::vector<float>, float volume)> func)
{
    m_functionsOnBufferFill.push_back(func);
}

void SoundProcessor::LoadSamples(std::string path)
{
    m_neuralNetwork->LoadData(path);
}

void SoundProcessor::AddSample(std::vector<float> FFT_output, std::vector<Stroke::Note> notes)
{
    std::vector<float> expected(POSSIBLE_NOTES_COUNT);
    for(auto& it : expected) {
        it = 0.0f;
    }
    QString name = "silnce";
    size_t i = 0;
    for(auto note : notes) {
        if(i == 0) {
            name = QString::fromStdString(Stroke::NoteToString(note));
        } else {
            name += "-" + QString::fromStdString(Stroke::NoteToString(note));
        }
        expected[static_cast<size_t>(note)] = 1.0f;
        i++;
    }
    m_neuralNetwork->AddData(name.toStdString(), NetworkDataSet(FFT_output, expected));
}

void SoundProcessor::RecordSample(std::vector<Stroke::Note> notes)
{
    bool beginning_state = m_soundCard->IsRunning();
    Start();

    std::cout << "wating for[ ";
    for(auto note : notes) {
        std::cout << Stroke::NoteToString(note) << " ";
    }
    std::cout << "]to be played..." << std::endl;
    usleep(300 K);
    std::cout << "..." << std::endl;

    if(notes.size() == 0) {
        while(avgVolume > RECORDING_SILENCE_THRESHOLD)usleep(10);

        usleep(RECORDING_START_WAIT_TIME_MILLISECONDS K);

        for(size_t i = 1; i <= RECORDING_TIMES_LIMIT && avgVolume < RECORDING_SILENCE_THRESHOLD; i++) {
            AddSample(m_FFT_output_realTime, notes);
            std::cout << "recorded! [" << i << "]" << std::endl;
            usleep(RECORDING_WAIT_TIME_MILLISECONDS K);
        }
    } else {
        while(avgVolume < RECORDING_VOLUME_THRESHOLD)usleep(10);

        usleep(RECORDING_START_WAIT_TIME_MILLISECONDS K);

        for(size_t i = 1; i <= RECORDING_TIMES_LIMIT && avgVolume > RECORDING_VOLUME_THRESHOLD; i++) {
            AddSample(m_FFT_output_realTime, notes);
            std::cout << "recorded! [" << i << "]" << std::endl;
            usleep(RECORDING_WAIT_TIME_MILLISECONDS K);
        }
    }
    std::cout << "done!" << std::endl;

    if(beginning_state == false) {
        Stop();
    }
}

void SoundProcessor::Learn(size_t times)
{
    m_neuralNetwork->Learn(times);
}


void SoundProcessor::Save(bool data, bool network)
{
    if(network)
        m_neuralNetwork->SaveNetwork(CONF::NETWORK_DATA::NET_CONF_PATH);
    if(data)
        m_neuralNetwork->SaveData(CONF::NETWORK_DATA::DATASET_PATH.toStdString());
}

void SoundProcessor::Load(bool data, bool network)
{
    if(network)
        m_neuralNetwork->LoadNetwork(CONF::NETWORK_DATA::NET_CONF_PATH);
    if(data)
        m_neuralNetwork->LoadData(CONF::NETWORK_DATA::DATASET_PATH.toStdString());
}

void SoundProcessor::InvokeOnBufferFill(int16_t *buffer, size_t bufferSize)
{
    FFT(buffer, bufferSize);
    m_notes_output_realTime = m_neuralNetwork->FeedForword(m_FFT_output_realTime);

    avgVolume = 0;
    for(size_t i = 0; i < bufferSize; i++) {
        avgVolume += abs(buffer[i]) * RECORDING_VOLUME_BOOST / MAX_SHORT;
    }

    avgVolume /= bufferSize;

    // notes to stroke...
    for(auto func : m_functionsOnBufferFill) {
        func(m_FFT_output_realTime, m_notes_output_realTime, avgVolume);
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
        //m_FFT_output_realTime[i] = std::tanh(30 * std::pow(m_FFT_output_realTime[i], 6));
    }
}
