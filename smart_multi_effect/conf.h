#ifndef CONF_H
#define CONF_H

#include <stdlib.h>
#include <stdint.h>
#include <vector>
#include <QAudioFormat>
#include <QString>
#include <EffectController/effect.h>
#include <QDir>
#include <QUrl>
#include <math.h>

#define Kilo * 1000
#define Mega * 1000000
#define Giga * 1000000000

namespace CONF
{
const QString MAIN_DIR = QDir::homePath() + "/.smart_multi_effect/";

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

    const uint8_t BUTTON1 = 26 ;
    const uint8_t BUTTON2 = 19 ;
    const uint8_t BUTTON3 = 13;
    const uint8_t BUTTON4 = 6;
    const uint8_t BUTTON5 = 5;

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
    const int CHANNEL = 0; //start from 0
    const QString CODEC = "";
    const int SAMPLE_RATE = 8000;
    const int SAMPLE_SIZE = 16;
    const auto SAMPLE_FORMAT = QAudioFormat::SignedInt;
}

namespace SOUND_PROCCESSING {
    const size_t BUFFER_FILL_SIZE = SOUND_CARD::BUFFER_SIZE * 1/2;
    const uint BUFFER_FILL_UTIME = 1 Mega * BUFFER_FILL_SIZE / SOUND_CARD::SAMPLE_RATE;
    const size_t FFT_SIZE = SOUND_CARD::BUFFER_SIZE / 2;
    const double RECORDING_VOLUME_FACTOR = std::pow(2, -(SOUND_CARD::SAMPLE_SIZE - 1));
    const uint RECORDING_WAIT_UTIME = BUFFER_FILL_UTIME * 1;
    const uint RECORDING_START_WAIT_UTIME = BUFFER_FILL_UTIME * 0;
    const size_t RECORDING_LIMIT = 10;
}

namespace NOTE_RECOGNITION {
    const float NOTE_THRESHOLD = 0.5f;
    const float OCTAVE_THRESHOLD = 0.5f;

    const uint8_t NOTES_IN_OCTAVE = 12;
    const uint8_t OCTAVE_LEVEL_COUNT = 3;

    const std::vector<size_t> FFT_TO_NOTE_NETWORK_STRUCTURE = {SOUND_PROCCESSING::FFT_SIZE, SOUND_PROCCESSING::FFT_SIZE * 2, NOTES_IN_OCTAVE};
    const std::vector<size_t> FFT_TO_OCTAVE_NETWORK_STRUCTURE = {SOUND_PROCCESSING::FFT_SIZE, SOUND_PROCCESSING::FFT_SIZE * 2, OCTAVE_LEVEL_COUNT};

    const double VOLUMELEVEL_VERYLOW_THRESHOLD = 0.0005;
    const double VOLUMELEVEL_LOW_THRESHOLD = 0.001;
    const double VOLUMELEVEL_MID_THRESHOLD = 0.005;
    const double VOLUMELEVEL_HIGH_THRESHOLD = 0.03;
    const double VOLUMELEVEL_VERYHIGH_THRESHOLD = 0.08;

    namespace NETWORK_DATA {
        const QString NETWORK_DATASET_FILE = "data.data";
        const QString NETWORK_DATA_ENDING = ".data";
        const QString FFT_TO_NOTE_NET_PATH = MAIN_DIR + "NetworkData/notes_net.data";
        const QString FFT_TO_OCTAVE_NET_PATH = MAIN_DIR + "NetworkData/octave_net.data";
        const QString NOTES_DATASET_DIR_PATH = MAIN_DIR + "NetworkData/RecordedData/Notes/";
        const QString OCTAVES_DATASET_DIR_PATH = MAIN_DIR + "NetworkData/RecordedData/Octaves/";
    }
}

namespace GUI_PARAMETERS {
    namespace MAIN_WINDOW {
        const QUrl MAIN_URL("qrc:/main.qml");
        const QString MAIN_WINDOW = "window";
        const QString MAIN_VIEW_AREA = "viewArea";
        const QString BUTTONS_AREA = "buttonsArea";
    }

    namespace SONGS_PAGE {
        const QUrl SONGS_URL("qrc:/Pages/SongsPage.qml");
        const QString SONG_FRAME_CONTANER = "SongPreset";

    }

    namespace PRESETS_PAGE {
        const QUrl PRESETS_URL("qrc:/Pages/PresetPage.qml");
        const QString PRESET_NAME = "presetText";

    }

    namespace PRESET_EDIT_PAGE {
        const QUrl PRESET_EDIT_URL("qrc:/EffectEdit/PresetEditPage.qml");
        const QString PRESET_HEADLINE = "presetHeadline";

        const QString EFFECT_1 = "effect_1";
        const QString EFFECT_2 = "effect_2";
        const QString EFFECT_3 = "effect_3";
        const QString EFFECT_4 = "effect_4";
        const QString EFFECT_5 = "effect_5";
        const QString EFFECT_6 = "effect_6";

    }

    namespace SONG_FRAME {
        const QUrl SONG_FRAME_URL("qrc:/Frames/SongFrame");
    }

    namespace CUSTON_BUTTON {
        const QUrl CUSTOM_BUTTON_URL("qrc:/ButtonsArea/CustomButton.qml");
        const QString BUTTON = "button";
        const QString BUTTON_TEXT = "buttonText";
        const QString BUTTON_1 = "button_1";
        const QString BUTTON_2 = "button_2";
        const QString BUTTON_3 = "button_3";
        const QString BUTTON_4 = "button_4";
        const QString BUTTON_5 = "button_5";
        const char IS_PRESSED[] = "isPressed";
        const QString BUTTON_COLOR = "#1e222e";
        const QString BUTTON_COLOR_PRESSED = "#2e323e";
        const std::vector<QString> BUTTONS = { BUTTON_1, BUTTON_2, BUTTON_3, BUTTON_4, BUTTON_5 };
    }

    namespace EFFECT_EDIT {
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

    namespace GENERAL_GUI_PROPERTIES_NAMES {
        const char LABLE_TEXT[] = "text";
        const char SWITCH_STATE[] = "checked";
        const char DIAL_VALUE[] = "value";
        const char COLOR[] = "color";
}

    namespace COLORS {
        const QString GREEN = "#00ff00";
        const QString RED = "#ff0000";
        const QString BRIGHT_BLUE = "#0099ff";
        const QString ORANGE = "#f48e06";
    }
}
};

#endif // CONF_H
