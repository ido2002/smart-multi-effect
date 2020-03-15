#include "soundprocessor.h"
#include "conf.h"
#include "FFT.h"
#include <iostream>
#include <cmath>
#include <unistd.h>
#include "noterecognition.h"



using namespace sound_processing;

using namespace CONF::SOUND_PROCCESSING;
using namespace CONF::SOUND_CARD;

SoundProcessor::SoundProcessor()
{
    //sets up note recognition
    m_noteRecognition = new NoteRecognition();

    //sets up sound card
    m_soundCard = new SoundCard(SAMPLE_BYTE_ORDER, CHANNEL_COUNT, CODEC,
                                SAMPLE_RATE, SAMPLE_SIZE, SAMPLE_FORMAT, BUFFER_SIZE);

    //sets up function on buffer fill
    m_soundCard->SetOnBufferFill([&](int16_t* buffer, size_t bufferSize){
        InvokeOnBufferFill(buffer, bufferSize);
    }, BUFFER_FILL_SIZE);
}

SoundProcessor::~SoundProcessor()
{
    if(m_soundCard)
        delete m_soundCard;
    if(m_noteRecognition)
        delete m_noteRecognition;
}

void SoundProcessor::Start() { m_soundCard->Start(); }

void SoundProcessor::Stop() { m_soundCard->Stop(); }

void SoundProcessor::AddFunctionOnBufferFill(std::function<void (int16_t *, size_t, Stroke)> func)
{
    m_functionsOnBufferFill.push_back(func);
}

void SoundProcessor::RecordNoteSample(std::vector<Stroke::Note> notes)
{
    using vol = Stroke::VolumeLevel;

    //start the soundcard
    bool soundCardInitialState = m_soundCard->IsRunning();
    if(soundCardInitialState == false)
        m_soundCard->Start();

    //wait for sound
    usleep(BUFFER_FILL_UTIME * 4);

    while(LastStroke == nullptr) {
        usleep(BUFFER_FILL_UTIME / 2);
    }

    while(LastStroke->volume < vol::medium) {
        usleep(BUFFER_FILL_UTIME / 2);
    }

    //record
    for(uint i = 0; i < RECORDING_LIMIT && LastStroke->volume > vol::very_low; i++) {
        m_noteRecognition->AddNoteDataSet(m_noteRecognition->getFFT(), notes);
    }

    //wait for silnce
    while(LastStroke->volume != vol::silence) {
        usleep(BUFFER_FILL_UTIME / 2);
    }

    //return soundcard to initial state
    if(soundCardInitialState == false){
        m_soundCard->Stop();
    }
}

void SoundProcessor::RecordOctaveSample(std::vector<float> octaves)
{
    using vol = Stroke::VolumeLevel;

    //start the soundcard
    bool soundCardInitialState = m_soundCard->IsRunning();
    if(soundCardInitialState == false)
        m_soundCard->Start();

    //wait for sound
    usleep(BUFFER_FILL_UTIME * 4);

    while(LastStroke->volume < vol::medium) {
        usleep(BUFFER_FILL_UTIME / 2);
    }

    //record
    for(uint i = 0; i < RECORDING_LIMIT && LastStroke->volume != vol::silence; i++) {
        m_noteRecognition->AddOctaveDataSet(m_noteRecognition->getFFT(), octaves);
    }

    //wait for silnce
    while(LastStroke->volume != vol::silence) {
        usleep(BUFFER_FILL_UTIME / 2);
    }

    //return soundcard to initial state
    if(soundCardInitialState == false){
        m_soundCard->Stop();
    }
}

void SoundProcessor::Learn(size_t notes, size_t octaves)
{
    m_noteRecognition->LearnNotes(notes);
    m_noteRecognition->LearnOctaves(octaves);
}

void SoundProcessor::InvokeOnBufferFill(int16_t *buffer, size_t bufferSize)
{
    if(LastStroke != nullptr) {
        delete LastStroke;
    }

    LastStroke = new Stroke(m_noteRecognition->BufferToStroke(buffer, bufferSize));

    if(Buffer_rt.size() != bufferSize) {
        Buffer_rt.resize(bufferSize);
    }

    for(size_t i = 0; i < bufferSize; i++) {
        Buffer_rt[i] = buffer[i];
    }

    for(auto func : m_functionsOnBufferFill) {
        func(buffer, bufferSize, *LastStroke);
    }
}
