#ifndef RIFFRECOGNITION_H
#define RIFFRECOGNITION_H

#include "SoundProcessing/stroke.h"
#include "riff.h"
#include <vector>

class RiffRecognition
{
public:
    enum playingStyle {nothing, high_solo, low_riff, struming, unknown};
    static std::string playingStyleToString(playingStyle ps);

public:
    RiffRecognition();

    playingStyle Update(sound_processing::Stroke stroke);
    bool CheckRiff(Riff riff);

    double compareStrokes(sound_processing::Stroke &s1, sound_processing::Stroke &s2);

    size_t FindFirstStroke(sound_processing::Stroke &s, size_t begin, size_t end, double minMatchPrecentage);

    size_t FindBestStroke(sound_processing::Stroke &s, size_t begin, size_t end, double minMatchPrecentage);

    size_t FindLastStroke(sound_processing::Stroke &s, size_t begin, size_t end, double minMatchPrecentage);

    long getDt(sound_processing::Stroke &s1, sound_processing::Stroke &s2);

private:
    std::vector<sound_processing::Stroke> strokes;
};

#endif // RIFFRECOGNITION_H
