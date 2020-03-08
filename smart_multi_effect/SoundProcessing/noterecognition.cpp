#include "noterecognition.h"
#include "FFT.h"
#include "conf.h"

using namespace CONF::NOTE_RECOGNITION;
using namespace CONF::SOUND_PROCCESSING;

sound_processing::NoteRecognition::NoteRecognition() :
    notesNetOutput(NOTES_IN_OCTAVE), octaveNetOutput(OCTAVE_LEVEL_COUNT)
{
    fftToNotesNet = new NeuralNetwork(FFT_TO_NOTE_NETWORK_STRUCTURE);
    fftToOctaveNet = new NeuralNetwork(FFT_TO_OCTAVE_NETWORK_STRUCTURE);
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
    for(size_t i = 0; i < bufferSize; i++) {
        m_FFT_re[i] = buffer[i] * RECORDING_VOLUME_FACTOR;
    }
    _FFT(1, static_cast<int>(log2(bufferSize)), &m_FFT_re[0], &m_FFT_im[0]);
    for(size_t i = 0; i < bufferSize / 2; i++) {
        fftOutput[i] = std::sqrt(m_FFT_re[i] * m_FFT_re[i] + m_FFT_im[i] * m_FFT_im[i]);
    }

    //notes
    notesNetOutput = fftToNotesNet->FeedForword(fftOutput);
    std::list<Stroke::Note> notes;
    for(size_t i = 0; i < notesNetOutput.size(); i++) {
        if(notesNetOutput[i] > NOTE_THRESHOLD) {
            notes.push_back(static_cast<Stroke::Note>(i));
        }
    }

    //octave
    octaveNetOutput = fftToOctaveNet->FeedForword(fftOutput);
    float octaveMaxValue = 0;
    float octaveMaxIndex = 0;
    for(size_t i = 0; i < octaveNetOutput.size(); i++) {
        if(octaveNetOutput[i] > octaveMaxValue) {
            octaveMaxValue = octaveNetOutput[i];
            octaveMaxIndex = i;
        }
    }
    Stroke::NoteOctave octave = static_cast<Stroke::NoteOctave>(octaveMaxIndex);

    //volume
    volumeLevel = BufferToVolumeLevel(buffer, bufferSize, sumOutput);

    //stroke
    Stroke stroke(start, notes, octave, volumeLevel);
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
    using namespace neural_network_tools;

    std::string category = "StrangeOctaveCategory";
    if(octaves[0] == 1) {
        category = "low octave";
    }
    if(octaves[1] == 1) {
        category = "mid octave";
    }
    if(octaves[2] == 1) {
        category = "high octave";
    }

    fftToOctaveNet->AddData(category, NetworkDataSet(FFT_output, octaves));
}

void sound_processing::NoteRecognition::LoadNetwork()
{
    using namespace NETWORK_DATA;
    fftToNotesNet->LoadNetwork(FFT_TO_NOTE_NET_PATH);
    fftToOctaveNet->LoadNetwork(FFT_TO_OCTAVE_NET_PATH);
}

void sound_processing::NoteRecognition::SaveNetwork()
{
    using namespace NETWORK_DATA;
    fftToNotesNet->SaveNetwork(FFT_TO_NOTE_NET_PATH);
    fftToOctaveNet->SaveNetwork(FFT_TO_OCTAVE_NET_PATH);
}

void sound_processing::NoteRecognition::LoadNetworkDataSets()
{
    using namespace NETWORK_DATA;
    fftToNotesNet->LoadData(NOTES_DATASET_DIR_PATH.toStdString());
    fftToOctaveNet->LoadData(OCTAVES_DATASET_DIR_PATH.toStdString());
}

void sound_processing::NoteRecognition::SaveNetworkDataSets()
{
    using namespace NETWORK_DATA;
    fftToNotesNet->SaveData(NOTES_DATASET_DIR_PATH.toStdString());
    fftToOctaveNet->SaveData(OCTAVES_DATASET_DIR_PATH.toStdString());
}

void sound_processing::NoteRecognition::LearnOctaves(size_t times)
{
    fftToOctaveNet->Learn(times);
}

void sound_processing::NoteRecognition::LearnNotes(size_t times)
{
    fftToNotesNet->Learn(times);
}
