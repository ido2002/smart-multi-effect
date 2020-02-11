#ifndef EFFECTHardware_H
#define EFFECTHardware_H

//done!

#include "potentiometer.h"
#include "gpiocontrol.h"
#include <map>

namespace hardware_ctrl {
    class Effect
    {
    public:
        enum EffectType {booster = 10, compressor, overdrive, distortion,
                         eq=20, noisegate,
                         delay=30, reverb,
                         chorus=40, phazer, flanger, tremolo,
                         other=1, null = 0};
        enum EffectControlLayoutEllements { Gain = 1, Drive = 1,
                                            Tone = 2, Low = 4, Mid = 8, High = 16,
                                            Mix = 32, Volume = 64,
                                            Delay = 128, Rate = 128, Speed = 128,
                                            Repeat = 256, Regen = 256, Depth = 256,
                                            Width = 512, Manual = 1024,
                                            Other1 = 2048, Other2 = 4096, Other3 = 8192, Other4 = 16384, Other5 = 32768, Other6 = 65536,
                                            Non = 0};
        static std::string LayoutEllementToString(EffectControlLayoutEllements element);
    public:
        Effect(int ioPin, EffectType effectType, uint64_t layoutElements);
        ~Effect();

        bool SetPotentiometer(EffectControlLayoutEllements element, uint8_t ioPin);
        Potentiometer* GetPotentiometer(EffectControlLayoutEllements element);

        void On();
        void Off();

    private:
        GpioControl* m_relay = nullptr;
        EffectType m_effectType;
        uint64_t m_layoutElements;
    public:
        std::map<EffectControlLayoutEllements, Potentiometer*> m_potentiometers;
    };
}



#endif // EFFECTHardware_H
