#include "stroke.h"

std::string Stroke::NoteToString(Stroke::Note note)
{
    std::string str = "";
    switch (note%12) {
    case A0:
        str += "A";
        break;
    case Bb0:
        str += "Bb";
        break;
    case B0:
        str += "B";
        break;
    case C0:
        str += "C";
        break;
    case Db0:
        str += "Db";
        break;
    case D0:
        str += "D";
        break;
    case Eb0:
        str += "Eb";
        break;
    case E0:
        str += "E";
        break;
    case F0:
        str += "F";
        break;
    case Gb0:
        str += "Gb";
        break;
    case G0:
        str += "G";
        break;
    case Ab0:
        str += "Ab";
        break;
    default:
        str += "Error";
        break;
    }

    str += std::to_string(static_cast<int>(note/12));

    return str;
}

Stroke::Note Stroke::StringToNote(std::string str)
{
    Note note;
    switch (str[0]) {
    case 'A':
        note = A0;
        break;
    case 'B':
        note = B0;
        break;
    case 'C':
        note = C0;
        break;
    case 'D':
        note = D0;
        break;
    case 'E':
        note = E0;
        break;
    case 'F':
        note = F0;
        break;
    case 'G':
        note = G0;
        break;
    default:
        note = A0;
        break;
    }

    int octave = 0;

    if(str.size() == 3 && str[1] == 'b') {
        if(note == A0) {
            note = Ab0;
        } else {
            note = static_cast<Note>(note - 1);
        }
        octave = static_cast<int>(str[2] - '0');
    }
    if(str.size() == 2) {
        octave = static_cast<int>(str[1] - '0');
    }

    note = static_cast<Note>(note + 12 * octave);

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

Stroke::Stroke(TimePoint start, std::list<Note> notes, VolumeLevel volume)
{
    this->start = start;
    this->notes = notes;
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
