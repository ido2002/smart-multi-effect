#include "gpiocontrol.h"

const QString PATH_BASE = "/sys/class/gpio/gpio";
const QString PATH_DIRECTION_END = "/direction";
const QString PATH_VALUE_END = "/value";
const QString PATH_EXPORT = "/sys/class/gpio/export";
const QString PATH_UNEXPORT = "/sys/class/gpio/unexport";
const QString OUT_MODE = "out";
const QString IN_MODE = "out";
const QString ON = "1";
const QString OFF = "0";

GpioControl::GpioControl(uint ioPin, bool negativeLogic, bool isOut, QObject *parent)
{
    m_isOut = isOut;
    m_negativeLogic = negativeLogic;
    m_ioPin = ioPin;

    QString ioPinS = QString::number(m_ioPin);
    m_file = new QFile(PATH_EXPORT);
    if(!m_file->open(QFile::WriteOnly)) {
        std::cout << "can't open " << PATH_EXPORT.data() << std::endl;
        return;
    }
    m_file->write(reinterpret_cast<char*>(ioPinS.data()), ioPinS.length());
    m_file->close();
    delete m_file;

    m_file = new QFile(PATH_BASE + QString::number(ioPin) + PATH_DIRECTION_END);
    if(!m_file->open(QFile::WriteOnly)) {
        std::cout << "can't open " << PATH_EXPORT.data() << std::endl;
        return;
    }
    m_file->write(reinterpret_cast<const char*>((m_isOut ? OUT_MODE : IN_MODE).data()), (m_isOut ? OUT_MODE : IN_MODE).length());
    m_file->close();
    delete m_file;

    m_file = new QFile(PATH_BASE + QString::number(ioPin) + PATH_VALUE_END);
    if(!m_file->open(m_isOut ? QFile::WriteOnly : QFile::ReadOnly)) {
        std::cout << "can't open " << PATH_EXPORT.data() << std::endl;
        return;
    }
}

GpioControl::~GpioControl()
{
    m_file->close();
    delete m_file;

    QString ioPinS = QString::number(m_ioPin);
    m_file = new QFile(PATH_UNEXPORT);
    if(!m_file->open(QFile::WriteOnly)) {
        std::cout << "can't open " << PATH_EXPORT.data() << std::endl;
        return;
    }
    m_file->write(reinterpret_cast<char*>(ioPinS.data()), ioPinS.length());
    m_file->close();
    delete m_file;
}

void GpioControl::On()
{
    if(!m_isOut) {
        std::cout << "can't write in read mode" << std::endl;
        return;
    }
    m_file->write(reinterpret_cast<const char*>((m_negativeLogic ? OFF : ON).data()),
                  (m_negativeLogic ? OFF : ON).length());
    m_current = true;
}

void GpioControl::Off()
{
    if(!m_isOut) {
        std::cout << "can't write in read mode" << std::endl;
        return;
    }
    m_file->write(reinterpret_cast<const char*>((!m_negativeLogic ? OFF : ON).data()),
                  (!m_negativeLogic ? OFF : ON).length());
    m_current = false;
}

bool GpioControl::Read()
{
    if(m_isOut) {
        return m_current;
    }
    bool last = m_current;
    bool temp = m_file->read(1) == "1";
    m_current = (m_negativeLogic ? !temp : temp);

    if(m_current != last) {
        emit ValueChanged(m_current);
    }

    return m_current;
}

void GpioControl::Tick(uint time_usec, bool tickOn)
{
    tickOn ? On() : Off();
    usleep(time_usec);
    !tickOn ? On() : Off();
}
