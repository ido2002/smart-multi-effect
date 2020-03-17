#ifndef RIFF_H
#define RIFF_H

#include "SoundProcessing/stroke.h"
#include <vector>
#include <QString>

struct Riff
{
    Riff();

    std::vector<sound_processing::Stroke> strokes;
    QString name;
};

#endif // RIFF_H
