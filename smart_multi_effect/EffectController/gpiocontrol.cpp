#include "gpiocontrol.h"

#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <chrono>
#include <string>

using namespace std;

GpioControl::GpioControl(int ioPin, bool negativeLogic)
{
    m_negativeLogic = negativeLogic;
    m_ioPin = ioPin;
    char path[32];
    sprintf(path, "/sys/class/gpio/gpio%d/value", ioPin);
    m_fd = open(path, O_RDWR);
    std::cout << path << ":" << m_fd << std::endl;
}

GpioControl::~GpioControl()
{
    close(m_fd);
}

void GpioControl::Write(bool on_off)
{
    if(m_negativeLogic)
        on_off = !on_off;
    std::string str = on_off ? "1\n" : "0\n";
    write(m_fd, &str[0], 2);
}

void GpioControl::Tick(uint time_usec, bool tickOn)
{
    Write(!tickOn);
    sleep_micro_sec(time_usec);
    Write(tickOn);
    sleep_micro_sec(time_usec);
    Write(!tickOn);
}

void GpioControl::sleep_micro_sec(uint usec)
{
    auto start = chrono::steady_clock::now();
    auto end = chrono::steady_clock::now();

    while(chrono::duration_cast<chrono::microseconds>(end - start).count() < usec)
        end = chrono::steady_clock::now();
}
