#include "stroke.h"

using namespace sound_processing;

std::string Stroke::NoteToString(Stroke::Note note)
{
    std::string str = "";
    switch (note%12) {
    case A1:
        str += "A";
        break;
    case Bb1:
        str += "Bb";
        break;
    case B1:
        str += "B";
        break;
    case C1:
        str += "C";
        break;
    case Db1:
        str += "Db";
        break;
    case D1:
        str += "D";
        break;
    case Eb1:
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
    case Ab1:
        str += "Ab";
        break;
    default:
        str += "Error";
        break;
    }

    int octave = note / 12;
    if(note%12 >= Ab1) {
        octave++;
    }

    str += std::to_string(static_cast<int>(octave));

    return str;
}

Stroke::Note Stroke::StringToNote(std::string str)
{
    Note note;
    switch (str[0]) {
    case 'A':
        note = A1;
        break;
    case 'B':
        note = B1;
        break;
    case 'C':
        note = C1;
        break;
    case 'D':
        note = D1;
        break;
    case 'E':
        note = E1;
        break;
    case 'F':
        note = F1;
        break;
    case 'G':
        note = G1;
        break;
    default:
        note = A1;
        break;
    }

    int octave = 0;

    if(str.size() == 3 && str[1] == 'b') {
        note = static_cast<Note>(note - 1);
        octave = static_cast<int>(str[2] - '0');
    }
    if(str.size() == 2) {
        octave = static_cast<int>(str[1] - '0');
    }

    if(note%12 >= Ab1) {
        octave -= 1;
    }

    note = static_cast<Note>(note%12 + 12 * octave);

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
