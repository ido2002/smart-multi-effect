#ifndef GPIOREAD_H
#define GPIOREAD_H

//done!

#include <string>

class GpioRead
{
public:
    GpioRead(int ioPin, bool negativeLogic = false, std::string name = "");
    ~GpioRead();

    bool Read();

    std::string GetName();

private:
    bool m_negativeLogic = false;
    int m_ioPin = 0;
    int m_fd = 0;
    char m_path[32];
    std::string m_name;
};

#endif // GPIOREAD_H
