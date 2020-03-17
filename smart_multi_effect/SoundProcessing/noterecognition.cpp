#include "noterecognition.h"
#include "FFT.h"
#include "conf.h"
#include <cmath>

using namespace CONF::NOTE_RECOGNITION;
using namespace CONF::SOUND_PROCCESSING;


std::vector<double> window;

void genWindow(size_t length) {
    if(window.size() == length) {
        return;
    }
    window.resize(length);
    for(size_t i = 0; i < length; i++) {
        window[i] = std::pow(std::sin((M_PI * i)/(length-1)), 2);
    }
}

sound_processing::NoteRecognition::NoteRecognition() :
    notesNetOutput(NOTES_IN_OCTAVE), octaveOutput(OCTAVE_LEVEL_COUNT)
{
    fftToNotesNet = new NeuralNetwork(FFT_TO_NOTE_NETWORK_STRUCTURE);
    //fftToOctaveNet = new NeuralNetwork(FFT_TO_OCTAVE_NETWORK_STRUCTURE);

}

sound_processing::Stroke::VolumeLevel BufferToVolumeLevel(int16_t *buffer, size_t bufferSize, double& sumOutput)
{
    using vol = sound_processing::Stroke::VolumeLevel;
    double sum = 0;
    for(size_t i = 0; i < bufferSize; i++) {
        sum += std::pow(buffer[0] * RECORDING_VOLUME_FACTOR, 2);
    }
    sum /= bufferSize;
    sum = std::sqrt(sum);
    sumOutput = sum;
    if(sum > VOLUMELEVEL_VERYHIGH_THRESHOLD) return vol::very_high;
    if(sum > VOLUMELEVEL_HIGH_THRESHOLD) return vol::high;
    if(sum > VOLUMELEVEL_MID_THRESHOLD) return vol::medium;
    if(sum > VOLUMELEVEL_LOW_THRESHOLD) return vol::low;
    if(sum > VOLUMELEVEL_VERYLOW_THRESHOLD) return vol::very_low;
    return vol::silence;
}

sound_processing::Stroke sound_processing::NoteRecognition::BufferToStroke(int16_t *buffer, size_t bufferSize)
{
    //start time:
    TimePoint start = std::chrono::steady_clock::now();

    //fft
    if(fftOutput.size() != bufferSize) {
        fftOutput.resize(bufferSize);
    }
    std::vector<double> m_FFT_re(bufferSize);
    std::vector<double> m_FFT_im(bufferSize, 0);
    genWindow(bufferSize);
    for(size_t i = 0; i < bufferSize; i++) {
        m_FFT_re[i] = buffer[i] * RECORDING_VOLUME_FACTOR * window[i];
    }
    _FFT(1, static_cast<int>(log2(bufferSize)), &m_FFT_re[0], &m_FFT_im[0]);

    for(size_t i = 0; i < bufferSize / 2; i++) {
        fftOutput[i] = std::sqrt(m_FFT_re[i] * m_FFT_re[i] + m_FFT_im[i] * m_FFT_im[i]);
        if(FFT_RES * i <= FFT_MIN_FREQ) {
            fftOutput[i] = 0;
        }
    }

    //notes
    notesNetOutput = fftToNotesNet->FeedForword(fftOutput);
    std::list<Stroke::Note> notes;
    float maxNoteValue = 0;
    for(size_t i = 0; i < notesNetOutput.size(); i++) {
        maxNoteValue = std::max(notesNetOutput[i], maxNoteValue);
    }
    for(size_t i = 0; i < notesNetOutput.size(); i++) {
        if(notesNetOutput[i] > maxNoteValue * NOTE_THRESHOLD) {
            notes.push_back(static_cast<Stroke::Note>(i));
        }
    }

    //octave
    octaveOutput[0] = 0;
    float FFT_BASS_max = 0;
    for(size_t i = FFT_BASS_MIN_FREQ / FFT_RES; i * FFT_RES < FFT_BASS_TOP_FREQ && i < FFT_SIZE; i++) {
        FFT_BASS_max = std::max(FFT_BASS_max, fftOutput[i]);
    }
    int FFT_BASS_counter = 0;
    for(size_t i = FFT_BASS_MIN_FREQ / FFT_RES; i * FFT_RES < FFT_BASS_TOP_FREQ && i < FFT_SIZE; i++) {
        if(fftOutput[i] > FFT_BASS_max * FFT_BASS_THRESHOLD) {
            octaveOutput[0] += fftOutput[i];
            FFT_BASS_counter++;
        }
    }
    octaveOutput[0] *= FFT_BASS_FACTOR / FFT_BASS_counter;

    octaveOutput[1] = 0;
    float FFT_MID_max = 0;
    for(size_t i = FFT_MID_MIN_FREQ / FFT_RES; i * FFT_RES < FFT_MID_TOP_FREQ && i < FFT_SIZE; i++) {
        FFT_MID_max = std::max(FFT_MID_max, fftOutput[i]);
    }
    int FFT_MID_counter = 0;
    for(size_t i = FFT_MID_MIN_FREQ / FFT_RES; i * FFT_RES < FFT_MID_TOP_FREQ && i < FFT_SIZE; i++) {
        if(fftOutput[i] > FFT_MID_max * FFT_MID_THRESHOLD) {
            octaveOutput[1] += fftOutput[i];
            FFT_MID_counter++;
        }
    }
    octaveOutput[1] *= FFT_MID_FACTOR / FFT_MID_counter;

    octaveOutput[2] = 0;
    float FFT_HIGH_max = 0;
    for(size_t i = FFT_HIGH_MIN_FREQ / FFT_RES; i * FFT_RES < FFT_HIGH_TOP_FREQ && i < FFT_SIZE; i++) {
        FFT_HIGH_max = std::max(FFT_HIGH_max, fftOutput[i]);
    }
    int FFT_HIGH_counter = 0;
    for(size_t i = FFT_HIGH_MIN_FREQ / FFT_RES; i * FFT_RES < FFT_HIGH_TOP_FREQ && i < FFT_SIZE; i++) {
        if(fftOutput[i] > FFT_HIGH_max * FFT_HIGH_THRESHOLD) {
            octaveOutput[2] += fftOutput[i];
            FFT_HIGH_counter++;
        }
    }
    octaveOutput[2] *= FFT_HIGH_FACTOR / FFT_HIGH_counter;


    float octaves[3] = {octaveOutput[0],
                        octaveOutput[1],
                        octaveOutput[2]};

    //volume
    volumeLevel = BufferToVolumeLevel(buffer, bufferSize, sumOutput);

    if(volumeLevel == Stroke::silence) {
        notes.clear();
        for(auto &n : notesNetOutput) {
            n = 0;
        }
        octaves[0] = 0;
        octaves[1] = 0;
        octaves[2] = 0;
        octaveOutput[0] = 0;
        octaveOutput[1] = 0;
        octaveOutput[2] = 0;
    }

    //stroke
    Stroke stroke(start, notes, octaves, volumeLevel);
    return stroke;
}

void sound_processing::NoteRecognition::AddNoteDataSet(std::vector<float> FFT_output, std::vector<sound_processing::Stroke::Note> notes)
{
    using namespace neural_network_tools;
    std::vector<float> expectedOutput(NOTES_IN_OCTAVE, 0.0f);
    for(auto note : notes) {
        expectedOutput[(size_t)note] = 1.0f;
    }

    std::string category = "";
    if(notes.size() == 0) {
        category = "no notes";
    }
    for(auto note : notes) {
        category += Stroke::NoteToString(note);
    }

    fftToNotesNet->AddData(category, NetworkDataSet(FFT_output, expectedOutput));
}

void sound_processing::NoteRecognition::AddOctaveDataSet(std::vector<float> FFT_output, std::vector<float> octaves)
{
//    using namespace neural_network_tools;

//    std::string category = "StrangeOctaveCategory";
//    if(octaves[0] == 1) {
//        category = "low octave";
//    }
//    if(octaves[1] == 1) {
//        category = "mid octave";
//    }
//    if(octaves[2] == 1) {
//        category = "high octave";
//    }

//    fftToOctaveNet->AddData(category, NetworkDataSet(FFT_output, octaves));
}

void sound_processing::NoteRecognition::Load(bool note_net, bool octave_net, bool note_data, bool octave_data)
{
    using namespace NETWORK_DATA;
    if(note_net) fftToNotesNet->LoadNetwork(FFT_TO_NOTE_NET_PATH);
    //if(octave_net) fftToOctaveNet->LoadNetwork(FFT_TO_OCTAVE_NET_PATH);
    if(note_data) fftToNotesNet->LoadData(NOTES_DATASET_DIR_PATH.toStdString());
    //if(octave_data) fftToOctaveNet->LoadData(OCTAVES_DATASET_DIR_PATH.toStdString());
}

void sound_processing::NoteRecognition::Save(bool note_net, bool octave_net, bool note_data, bool octave_data)
{
    using namespace NETWORK_DATA;
    if(note_net) fftToNotesNet->SaveNetwork(FFT_TO_NOTE_NET_PATH);
    //if(octave_net) fftToOctaveNet->SaveNetwork(FFT_TO_OCTAVE_NET_PATH);
    if(note_data) fftToNotesNet->SaveData(NOTES_DATASET_DIR_PATH.toStdString());
    //if(octave_data) fftToOctaveNet->SaveData(OCTAVES_DATASET_DIR_PATH.toStdString());
}

void sound_processing::NoteRecognition::Load()
{
    using namespace NETWORK_DATA;
    fftToNotesNet->LoadNetwork(FFT_TO_NOTE_NET_PATH);
    //fftToOctaveNet->LoadNetwork(FFT_TO_OCTAVE_NET_PATH);
    fftToNotesNet->LoadData(NOTES_DATASET_DIR_PATH.toStdString());
    //fftToOctaveNet->LoadData(OCTAVES_DATASET_DIR_PATH.toStdString());
}

void sound_processing::NoteRecognition::Save()
{
    using namespace NETWORK_DATA;
    fftToNotesNet->SaveNetwork(FFT_TO_NOTE_NET_PATH);
    //fftToOctaveNet->SaveNetwork(FFT_TO_OCTAVE_NET_PATH);
    fftToNotesNet->SaveData(NOTES_DATASET_DIR_PATH.toStdString());
    //fftToOctaveNet->SaveData(OCTAVES_DATASET_DIR_PATH.toStdString());
}

void sound_processing::NoteRecognition::LoadNetwork()
{
    using namespace NETWORK_DATA;
    fftToNotesNet->LoadNetwork(FFT_TO_NOTE_NET_PATH);
    //fftToOctaveNet->LoadNetwork(FFT_TO_OCTAVE_NET_PATH);
}

void sound_processing::NoteRecognition::SaveNetwork()
{
    using namespace NETWORK_DATA;
    fftToNotesNet->SaveNetwork(FFT_TO_NOTE_NET_PATH);
    //fftToOctaveNet->SaveNetwork(FFT_TO_OCTAVE_NET_PATH);
}

void sound_processing::NoteRecognition::LoadNetworkDataSets()
{
    using namespace NETWORK_DATA;
    fftToNotesNet->LoadData(NOTES_DATASET_DIR_PATH.toStdString());
    //fftToOctaveNet->LoadData(OCTAVES_DATASET_DIR_PATH.toStdString());
}

void sound_processing::NoteRecognition::SaveNetworkDataSets()
{
    using namespace NETWORK_DATA;
    fftToNotesNet->SaveData(NOTES_DATASET_DIR_PATH.toStdString());
    //fftToOctaveNet->SaveData(OCTAVES_DATASET_DIR_PATH.toStdString());
}

void sound_processing::NoteRecognition::LearnOctaves(size_t times)
{
    //fftToOctaveNet->Learn(times);
}

void sound_processing::NoteRecognition::LearnNotes(size_t times)
{
    fftToNotesNet->Learn(times);
}
