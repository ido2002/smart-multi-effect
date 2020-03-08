#ifndef STROKE_H
#define STROKE_H

#include <chrono>
#include <list>
#include <string>

namespace sound_processing {

    typedef std::chrono::steady_clock::time_point TimePoint;

    struct Stroke
    {
    public:
        enum Note {Ab = 0, A, Bb, B, C, Db, D, Eb, E, F, Gb, G};
        enum NoteOctave {Low = 0, Mid, High};
        enum VolumeLevel {silence, very_low, low, medium, high, very_high};

        static std::string NoteToString(Note note);
        static Note StringToNote(std::string str);
        static std::string VolumeLevelToString(VolumeLevel volumeLevel);
        static std::string NoteOctaveToString(NoteOctave noteOctave);

    public:
        Stroke(TimePoint start, std::list<Note> notes, NoteOctave octave, VolumeLevel volume);

        static bool CompareNotes(Stroke& s1, Stroke& s2);

    public:
        TimePoint start;
        std::list<Note> notes;
        NoteOctave octave;
        VolumeLevel volume;
    };
}
#endif // STROKE_H
