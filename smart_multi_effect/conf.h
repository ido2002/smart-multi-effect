#ifndef CONF_H
#define CONF_H

#include <stdlib.h>
#include <stdint.h>
#include <vector>
#include <QAudioFormat>
#include <QString>
#include <EffectController/effect.h>
#include <QUrl>

namespace CONF
{
namespace NAMES{
    const std::string OVERDRIVE = "OverDrive";
    const std::string DELAY = "Delay";
    const std::string TREMOLO = "Tremolo";
    const std::string SPEED = "Speed";
    const std::string VOLUME = "Volume";
    const std::string TONE = "Tone";
    const std::string GAIN = "Gain";
}

namespace HARDWARE {
    const uint8_t EFFECT_COUNT = 3;
    const uint8_t POTENTIOMETER_COUNT = 6;

    const uint8_t INC_PIN = 17;
    const uint8_t UD_PIN  = 27;

    const uint8_t P1_PIN  = 4 ;
    const uint8_t P2_PIN  = 23;
    const uint8_t P3_PIN  = 18;
    const uint8_t P4_PIN  = 12;
    const uint8_t P5_PIN  = 22;
    const uint8_t P6_PIN  = 24;

    const uint8_t RELAY_1 = 21;
    const uint8_t RELAY_2 = 20;
    const uint8_t RELAY_3 = 16;

    const uint8_t BUTTON1 = 5 ;
    const uint8_t BUTTON2 = 6 ;
    const uint8_t BUTTON3 = 13;
    const uint8_t BUTTON4 = 19;
    const uint8_t BUTTON5 = 26;

    const std::string P1_NAME = NAMES::SPEED;
    const std::string P2_NAME = NAMES::VOLUME;
    const std::string P3_NAME = NAMES::SPEED;
    const std::string P4_NAME = NAMES::VOLUME;
    const std::string P5_NAME = NAMES::TONE;
    const std::string P6_NAME = NAMES::GAIN;

    const hardware_ctrl::Effect::EffectControlLayoutEllements P1_TYPE = hardware_ctrl::Effect::Speed;
    const hardware_ctrl::Effect::EffectControlLayoutEllements P2_TYPE = hardware_ctrl::Effect::Volume;
    const hardware_ctrl::Effect::EffectControlLayoutEllements P3_TYPE = hardware_ctrl::Effect::Speed;
    const hardware_ctrl::Effect::EffectControlLayoutEllements P4_TYPE = hardware_ctrl::Effect::Volume;
    const hardware_ctrl::Effect::EffectControlLayoutEllements P5_TYPE = hardware_ctrl::Effect::Tone;
    const hardware_ctrl::Effect::EffectControlLayoutEllements P6_TYPE = hardware_ctrl::Effect::Gain;

    const hardware_ctrl::Effect::EffectType EFFECT_1_TYPE = hardware_ctrl::Effect::tremolo;
    const hardware_ctrl::Effect::EffectType EFFECT_2_TYPE = hardware_ctrl::Effect::delay;
    const hardware_ctrl::Effect::EffectType EFFECT_3_TYPE = hardware_ctrl::Effect::overdrive;

    const uint64_t EFFECT_1_LAYOUT = hardware_ctrl::Effect::Speed;
    const uint64_t EFFECT_2_LAYOUT = hardware_ctrl::Effect::Speed | hardware_ctrl::Effect::Volume;
    const uint64_t EFFECT_3_LAYOUT = hardware_ctrl::Effect::Volume | hardware_ctrl::Effect::Tone | hardware_ctrl::Effect::Gain;

    const uint64_t EFFECT_1_POTENTIOMETERS = 1 << 0;
    const uint64_t EFFECT_2_POTENTIOMETERS = 1 << 1 | 1 << 2;
    const uint64_t EFFECT_3_POTENTIOMETERS = 1 << 3 | 1 << 4 | 1 << 5;

    const std::string EFFECT_1_NAME = NAMES::TREMOLO;
    const std::string EFFECT_2_NAME = NAMES::DELAY;
    const std::string EFFECT_3_NAME = NAMES::OVERDRIVE;
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
    const size_t BUFFER_FILL_SIZE = SOUND_CARD::BUFFER_SIZE * 1/2; // editable
    const size_t POSSIBLE_NOTES_COUNT = 48; //48 - E0 - E4
    const size_t FFT_COUNT = SOUND_CARD::BUFFER_SIZE / 2;
    const size_t FFT_FILTER = 4;
    const double FFT_FILTER_FACTOR = 0.5;
    const std::vector<size_t> NEURAL_NETWORK_STRUCTURE = {FFT_COUNT/4, /*FFT_COUNT/4,*/ /*POSSIBLE_NOTES_COUNT*2,*/ POSSIBLE_NOTES_COUNT};
    const uint RECORDING_WAIT_TIME_MILLISECONDS = (1000 * SOUND_CARD::BUFFER_SIZE / SOUND_CARD::SAMPLE_RATE) * 4 / 3;
    const uint RECORDING_START_WAIT_TIME_MILLISECONDS = 10;
    const size_t RECORDING_TIMES_LIMIT = 10;
    const float RECORDING_VOLUME_THRESHOLD = 0.15f;
    const float RECORDING_SILENCE_THRESHOLD = 0.005f;
    const float RECORDING_VOLUME_BOOST = 100;
}

namespace NETWORK_DATA {
    const QString NET_CONF_PATH = "/home/ido/Development/prototypeCode/NetworkData/net.data";
    const QString DATASET_PATH = "/home/ido/Development/prototypeCode/NetworkData/RecordedData/";
}

namespace GUI_PARAMETERS {
namespace EFFECT_EDIT_PARAMETERS {
    const QUrl EFFECT_EDIT3_URL("qrc:/EffectEdit/EffectEdit.qml");

    const QString DIAL1_NAME = "dial1";
    const QString DIAL2_NAME = "dial2";
    const QString DIAL3_NAME = "dial3";
    const QString DIAL4_NAME = "dial4";
    const QString DIAL5_NAME = "dial5";
    const QString DIAL6_NAME = "dial6";

    const QString SWITCH_NAME = "switch";

    const QString DIAL_NAME = "dial";
    const QString VALUE_LABLE_NAME = "valueLable";
    const QString TEXT_LABLE_NAME = "textLable";

    const QString EFFECT_LABLE_NAME = "effectNameLable";
}

namespace GENERAL_GUI_PARAMETERS {

}

namespace GENERAL_GUI_PROPERTIES_NAMES {
const char LABLE_TEXT[] = "text";
const char SWITCH_STATE[] = "position";
const char DIAL_VALUE[] = "value";
}
}
};

#endif // CONF_H
