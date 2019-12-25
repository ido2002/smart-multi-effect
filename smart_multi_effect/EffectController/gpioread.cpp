#include "gpioread.h"

#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <chrono>
#include <string>

GpioRead::GpioRead(int ioPin, bool negativeLogic, std::string name)
{
    m_negativeLogic = negativeLogic;
    m_ioPin = ioPin;
    sprintf(m_path, "/sys/class/gpio/gpio%d/value", ioPin);
    m_name = name;
    m_fd = open(m_path, O_RDWR);
}

GpioRead::~GpioRead()
{
    close(m_fd);
}

bool GpioRead::Read()
{
    char c;
    lseek(m_fd, 0, SEEK_SET);
    read(m_fd, &c, 1);
    return m_negativeLogic ? c=='0' : c=='1';
}

std::string GpioRead::GetName()
{
    return m_name;
}
