#ifndef CONF_H
#define CONF_H

#include <stdlib.h>
#include <stdint.h>
#include <vector>
#include <QAudioFormat>
#include <QString>

namespace CONF
{
namespace HARDWARE {
    const uint8_t INC_PIN = 17;
    const uint8_t UD_PIN  = 27;

    const uint8_t P1_PIN  = 4 ;
    const uint8_t P2_PIN  = 23;
    const uint8_t P3_PIN  = 18;
    const uint8_t P4_PIN  = 12;
    const uint8_t P5_PIN  = 22;
    const uint8_t P6_PIN  = 24;

    const uint8_t RELAY_1 = 20;
    const uint8_t RELAY_2 = 21;
    const uint8_t RELAY_3 = 16;

    const uint8_t BUTTON1 = 5 ;
    const uint8_t BUTTON2 = 6 ;
    const uint8_t BUTTON3 = 13;
    const uint8_t BUTTON4 = 19;
    const uint8_t BUTTON5 = 26;
}

namespace SOUND_CARD {
    const size_t BUFFER_SIZE = 1024 * 1;
    const auto SAMPLE_BYTE_ORDER = QAudioFormat::LittleEndian;
    const int CHANNEL_COUNT = 2;
    const QString CODEC = "";
    const int SAMPLE_RATE = 8000;
    const int SAMPLE_SIZE = 16;
    const auto SAMPLE_FORMAT = QAudioFormat::SignedInt;
}

namespace SOUND_PROCCESSING {
    const size_t BUFFER_FILL_SIZE = SOUND_CARD::BUFFER_SIZE * 1; // editable
    const size_t POSSIBLE_NOTES_COUNT = 60; //84
    const size_t FFT_COUNT = SOUND_CARD::BUFFER_SIZE / 2;
    const std::vector<size_t> NEURAL_NETWORK_STRUCTURE = {FFT_COUNT, /**/FFT_COUNT, /**/POSSIBLE_NOTES_COUNT*2, POSSIBLE_NOTES_COUNT};
    const uint RECORDING_WAIT_TIME_MILLISECONDS = 1000 * SOUND_CARD::BUFFER_SIZE / SOUND_CARD::SAMPLE_RATE;
    const uint RECORDING_START_WAIT_TIME_MILLISECONDS = 0;
    const size_t RECORDING_TIMES_LIMIT = 10;
    const float RECORDING_VOLUME_THRESHOLD = 0.05f;
    const float RECORDING_SILENCE_THRESHOLD = 0.01f;
    const float RECORDING_VOLUME_BOOST = 100;
}

namespace NETWORK_DATA {
    const QString NET_CONF_PATH = "/home/ido/Development/prototypeCode/NetworkData/net.data";
    const QString DATASET_PATH = "/home/ido/Development/prototypeCode/NetworkData/RecordedData/";
}
};

#endif // CONF_H
