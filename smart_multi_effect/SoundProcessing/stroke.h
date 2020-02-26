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
        enum Note {     E0, F0, Gb0, G0, Ab1, A1, Bb1, B1, C1, Db1, D1,
                   Eb1, E1, F1, Gb1, G1, Ab2, A2, Bb2, B2, C2, Db2, D2,
                   Eb2, E2, F2, Gb2, G2, Ab3, A3, Bb3, B3, C3, Db3, D3,
                   Eb3, E3, F3, Gb3, G3, Ab4, A4, Bb4, B4, C4, Db4, D4,
                   Eb4, E4};
        enum VolumeLevel {silence, very_low, low, medium, high, very_high};

        static std::string NoteToString(Note note);
        static Note StringToNote(std::string str);
        static std::string VolumeLevelToString(VolumeLevel volumeLevel);

    public:
        Stroke(TimePoint start, std::list<Note> notes, VolumeLevel volume);

        static bool CompareNotes(Stroke& s1, Stroke& s2);

    public:
        TimePoint start;
        std::list<Note> notes;
        VolumeLevel volume;
    };
}
#endif // STROKE_H
