#include "riffrecognition.h"
#include "conf.h"

using namespace CONF::RIFF_RECOGNITION;
using namespace sound_processing;
using namespace std::chrono;

std::string RiffRecognition::playingStyleToString(RiffRecognition::playingStyle ps)
{
    switch (ps) {
    case nothing:
        return "nothing";
        break;
    case high_solo:
        return "high_solo";
        break;
    case low_riff:
        return "low_riff";
        break;
    case struming:
        return "struming";
        break;
    case unknown:
        return "unknown";
        break;
    }
    return "playingStyle.toString error! [ps]: " + std::to_string(ps);
}

RiffRecognition::RiffRecognition()
{

}

RiffRecognition::playingStyle RiffRecognition::Update(sound_processing::Stroke stroke)
{
    if(strokes.size() > 0 && compareStrokes(strokes[strokes.size()-1], stroke) >= 0.8) {

    } else {
        strokes.push_back(stroke);
    }

    if(stroke.volume < Stroke::high || stroke.octaves[0] + stroke.octaves[2] < 0.5) {
        return nothing;
    }

    if(stroke.octaves[0] > 0.4 && stroke.octaves[2] < 0.3) {
        return low_riff;
    }

    if(stroke.octaves[0] < 0.03) {
        return high_solo;
    }

    if(stroke.octaves[0] > 0.1 && stroke.octaves[0] < 0.25 && stroke.octaves[2] > 0.6) {
        return struming;
    }

    return unknown;
}

bool RiffRecognition::CheckRiff(Riff riff)
{
    auto dtime = riff.strokes[riff.strokes.size()-1].start - riff.strokes[0].start;
    milliseconds time_ms = duration_cast<milliseconds>(dtime);
}

double RiffRecognition::compareStrokes(Stroke &s1, Stroke &s2)
{
    int d_volume = std::abs(s1.volume - s2.volume);
    double p_volume = (1 - d_volume*VOLUME_MATCH_FACTOR) * VOLUME_MATCH_WHEIGTH;

    int d_notesCount = std::abs((long)s1.notes.size() - (long)s2.notes.size());
    double p_notesCount = (1 - d_notesCount*NOTES_COUNT_MATCH_FACTOR) * NOTES_COUNT_MATCH_WHEIGTH;

    double p_notes = 0;
    if(s1.notes.size() == 0 || s2.notes.size() == 0) {
        p_notes = 1 - d_notesCount*NOTES_COUNT_MATCH_FACTOR;
    } else {
        for(auto note : s1.notes) {
            double found = 0;
            for(auto n : s2.notes) {
                int delta = std::abs(note - n);
                if(delta >= 6) {
                    delta = 12 - delta;
                }

                if(delta == 0) {
                    found = 1;
                    break;
                }

                if(found < 0.3 && delta == 1) {
                    found = 0.3;
                }

                if(found < 0.05 && delta == 2) {
                    found = 0.05;
                }
            }
            p_notes += found / s1.notes.size();
        }
    }
    p_notes *= NOTES_MATCH_WHEIGTH;

    float d_bass = std::abs(s1.octaves[0] - s2.octaves[0]);
    double p_bass = (1 - d_bass * BASS_MATCH_FACTOR) * BASS_MATCH_WHEIGTH;

    float d_high = std::abs(s1.octaves[2] - s2.octaves[2]);
    double p_high = (1 - d_high * HIGH_MATCH_FACTOR) * HIGH_MATCH_WHEIGTH;


    return p_volume + p_notesCount + p_notes + p_bass + p_high;
}

size_t RiffRecognition::FindFirstStroke(sound_processing::Stroke &s, size_t begin, size_t end, double minMatchPrecentage)
{
    for(size_t i = begin; i < end && i < strokes.size(); i++) {
        if(compareStrokes(s, strokes[i]) > minMatchPrecentage) {
            return i;
        }
    }
    return 0;
}

size_t RiffRecognition::FindBestStroke(Stroke &s, size_t begin, size_t end, double minMatchPrecentage)
{
    size_t bestIndex = 0;
    double bestMatch = minMatchPrecentage;
    for(size_t i = begin; i < end && i < strokes.size(); i++) {
        double match = compareStrokes(s, strokes[i]);
        if(match >= bestMatch) {
            bestMatch = match;
            bestIndex = i;
        }
    }
    return bestIndex;
}

size_t RiffRecognition::FindLastStroke(sound_processing::Stroke &s, size_t begin, size_t end, double minMatchPrecentage)
{
    end = std::min(end, strokes.size()-1);
    for(size_t i = end; i < begin && i > 0; i--) {
        if(compareStrokes(s, strokes[i]) > minMatchPrecentage) {
            return i;
        }
    }
    return 0;
}

long RiffRecognition::getDt(Stroke &s1, Stroke &s2)
{
    auto dtime = s2.start - s1.start;
    milliseconds time_ms = duration_cast<milliseconds>(dtime);
    return std::abs(time_ms.count());
}
