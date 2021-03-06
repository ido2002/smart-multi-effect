#ifndef GPIOCONTROL_H
#define GPIOCONTROL_H

//done!

#include <stdlib.h>

namespace hardware_ctrl {
    class GpioControl
    {
    public:
        GpioControl(int ioPin, bool negativeLogic = false);
        ~GpioControl();

        void Write(bool on_off);
        void Tick(uint time_usec, bool tickOn = true);
        static void sleep_micro_sec(uint usec);

    public:
        bool m_negativeLogic = false;
        int m_ioPin = 0;
        int m_fd = 0;
        bool m_lastValue;
    };
}
#endif // GPIOCONTROL_H
