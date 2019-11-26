#include "gpiocontrol.h"

const QString PATH_BASE = "/sys/class/gpio/gpio";
const QString PATH_DIRECTION_END = "/direction";
const QString PATH_VALUE_END = "/value";
const QString PATH_EXPORT = "/sys/class/gpio/export";
const QString OUT_MOD = "out";
const QString ON = "1";
const QString OFF = "0";

GpioControl::GpioControl(uint ioPin, bool negativeLogic, QObject *parent) : QObject(parent)
{
    m_negativeLogic = negativeLogic;

    QString ioPinS = QString::number(ioPin);
    m_file = new QFile(PATH_EXPORT);
    m_file->open(QFile::WriteOnly);
    m_file->write(reinterpret_cast<char*>(ioPinS.data()), ioPinS.length());
    m_file->close();
    delete m_file;

    m_file = new QFile(PATH_BASE + QString::number(ioPin) + PATH_DIRECTION_END);
    m_file->open(QFile::WriteOnly);
    m_file->write(reinterpret_cast<const char*>(OUT_MOD.data()), OUT_MOD.length());
    m_file->close();
    delete m_file;

    m_file = new QFile(PATH_BASE + QString::number(ioPin) + PATH_VALUE_END);
    m_file->open(QFile::WriteOnly);
}

GpioControl::~GpioControl()
{
    m_file->close();
    delete m_file;
}

void GpioControl::On()
{
    m_file->write(reinterpret_cast<const char*>((m_negativeLogic ? OFF : ON).data()),
                  (m_negativeLogic ? OFF : ON).length());
}

void GpioControl::Off()
{
    m_file->write(reinterpret_cast<const char*>((!m_negativeLogic ? OFF : ON).data()),
                  (!m_negativeLogic ? OFF : ON).length());
}
