#include "stroke.h"

using namespace sound_processing;

std::string Stroke::NoteToString(Stroke::Note note)
{
    std::string str = "";
    switch (note%12) {
    case A:
        str += "A";
        break;
    case Bb:
        str += "Bb";
        break;
    case B:
        str += "B";
        break;
    case C:
        str += "C";
        break;
    case Db:
        str += "Db";
        break;
    case D:
        str += "D";
        break;
    case Eb:
        str += "Eb";
        break;
    case E:
        str += "E";
        break;
    case F:
        str += "F";
        break;
    case Gb:
        str += "Gb";
        break;
    case G:
        str += "G";
        break;
    case Ab:
        str += "Ab";
        break;
    default:
        str += "Error";
        break;
    }

    return str;
}

Stroke::Note Stroke::StringToNote(std::string str)
{
    Note note;
    switch (str[0]) {
    case 'A':
        note = A;
        break;
    case 'B':
        note = B;
        break;
    case 'C':
        note = C;
        break;
    case 'D':
        note = D;
        break;
    case 'E':
        note = E;
        break;
    case 'F':
        note = F;
        break;
    case 'G':
        note = G;
        break;
    default:
        note = A;
        break;
    }

    if(str.size() == 3 && str[1] == 'b') {
        note = static_cast<Note>(note - 1);
    }

    return note;
}

std::string Stroke::VolumeLevelToString(Stroke::VolumeLevel volumeLevel)
{
    switch (volumeLevel) {
    case silence:
        return "silence";
    case very_low:
        return "very_low";
    case low:
        return "low";
    case medium:
        return "medium";
    case high:
        return "high";
    case very_high:
        return "very_high";
    }
    return "error";
}

std::string Stroke::NoteOctaveToString(Stroke::NoteOctave noteOctave)
{
    switch (noteOctave) {
    case Low:
        return "Low";
    case Mid:
        return "Mid";
    case High:
        return "High";
    }
    return "error";
}

Stroke::Stroke(TimePoint start, std::list<Stroke::Note> notes, float octaves[3], Stroke::VolumeLevel volume)
{
    this->start = start;
    this->notes = notes;
    this->octaves[0] = octaves[0];
    this->octaves[1] = octaves[1];
    this->octaves[2] = octaves[2];
    this->volume = volume;
}

bool Stroke::CompareNotes(Stroke &s1, Stroke &s2) {
    if(s1.notes.size() != s2.notes.size()) {
        return false;
    }
    for(Note n1 : s1.notes) {
        bool found = false;
        for(Note n2 : s2.notes) {
            if(n1 == n2) {
                found = true;
                break;
            }
        }
        if(!found) {
            return false;
        }
    }
    return true;
}
