#ifndef NOTERECOGNITION_H
#define NOTERECOGNITION_H

#include "stroke.h"
#include <vector>

namespace sound_processing {
    class NoteRecognition
    {
    public:
        NoteRecognition();

        Stroke BufferToStroke(int16_t* buffer, size_t bufferSize);
    };
}

#endif // NOTERECOGNITION_H
