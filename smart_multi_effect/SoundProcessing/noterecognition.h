#ifndef NOTERECOGNITION_H
#define NOTERECOGNITION_H

#include <vector>
#include <map>
#include "stroke.h"
#include "neuralnetwork.h"
#include <QVariantMap>

namespace sound_processing {
    class NoteRecognition
    {
    public:
        NoteRecognition();

        Stroke BufferToStroke(int16_t* buffer, size_t bufferSize);

        void updpateFFT(int16_t* buffer, size_t bufferSize);
        void updateNotes();
        void updateOctave();

        void AddNoteDataSet(std::vector<float> FFT_output, std::vector<Stroke::Note> notes);
        void AddOctaveDataSet(std::vector<float> FFT_output, std::vector<float> octaves);

        void Load(bool note_net, bool octave_net, bool note_data, bool octave_data);
        void Save(bool note_net, bool octave_net, bool note_data, bool octave_data);

        void Load();
        void Save();

        void LoadNetwork();
        void SaveNetwork();

        void LoadNetworkDataSets();
        void SaveNetworkDataSets();

        void LearnOctaves(size_t times = 500);
        void LearnNotes(size_t times = 500);

        double getSumOutput() { return sumOutput; }
        Stroke::VolumeLevel getVolumeLevel() { return volumeLevel; }
        std::string getVolumeLevelStr() { return Stroke::VolumeLevelToString(volumeLevel); }

        std::vector<float> getFFT() { return fftOutput; }
        std::vector<float> getNotes() { return notesNetOutput; }
        std::vector<float> getOctave() { return octaveOutput; }

    private:
        NeuralNetwork* fftToNotesNet = nullptr;
        //NeuralNetwork* fftToOctaveNet = nullptr;
        double sumOutput = 0;
        Stroke::VolumeLevel volumeLevel = Stroke::silence;
        std::vector<float> notesNetOutput;
        std::vector<float> fftOutput;
        std::vector<float> octaveOutput;
    };
}

#endif // NOTERECOGNITION_H
