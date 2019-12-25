#include "potentiometer.h"

Potentiometer::Potentiometer(uint ioNumber, bool NegativeLogic, QObject *parent) : QObject(parent)
{
    m_chipSelectPin = new GpioControl(ioNumber, NegativeLogic);
}

Potentiometer::~Potentiometer()
{
    delete m_chipSelectPin;
}

void Potentiometer::SetTarget(uint target)
{
    m_targetValue = target;
}

uint Potentiometer::GetValue()
{
    return m_currentValue;
}

void Potentiometer::CS(bool on_off)
{
    on_off ? m_chipSelectPin->On() : m_chipSelectPin->Off();
}

bool Potentiometer::Check(bool increceUp)
{

}
