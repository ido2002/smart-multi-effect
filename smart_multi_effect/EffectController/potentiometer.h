#ifndef POTENTIOMETER_H
#define POTENTIOMETER_H

//done!

#include "gpiocontrol.h"

namespace hardware_ctrl {
    class Potentiometer
    {
    public:
        Potentiometer(int ioNumber, bool NegativeLogic = false);
        ~Potentiometer();

        void SetTarget(uint target);
        uint GetValue();
        uint GetTarget();
        void CS(bool on_off);
        bool Check(bool increceUp);
        void SetCurrentValue(uint value);

    private:
        GpioControl* m_chipSelectPin = nullptr;
        bool m_selected = false;
        uint m_currentValue = 0;
        uint m_targetValue = 0;
    };
}
#endif // POTENTIOMETER_H
