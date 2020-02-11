#include "potentiometer.h"

using namespace hardware_ctrl;

Potentiometer::Potentiometer(int ioNumber, bool NegativeLogic) :
    m_chipSelectPin(new GpioControl(ioNumber, NegativeLogic))
{

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

uint Potentiometer::GetTarget()
{
    return m_targetValue;
}

void Potentiometer::CS(bool on_off)
{
    m_chipSelectPin->Write(on_off);
    m_selected = on_off;
}

bool Potentiometer::Check(bool increceUp)
{
    if(increceUp) {
        if(m_currentValue >= m_targetValue) {
            CS(false);
            return true;
        } else {
            if(!m_selected)
                CS(true);
            m_currentValue++;
            return false;
        }
    } else {
        if(m_currentValue <= m_targetValue) {
            CS(false);
            return true;
        } else {
            if(!m_selected)
                CS(true);
            m_currentValue--;
            return false;
        }
    }
}

void Potentiometer::SetCurrentValue(uint value)
{
    m_currentValue = value;
}
