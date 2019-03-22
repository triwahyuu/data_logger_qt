#include "serial_core.h"

#include <QTime>
#include <QDebug>

SerialCore::SerialCore(QObject *parent) : QObject(parent)
{
    m_serial = new QSerialPort();
}

SerialCore::~SerialCore()
{
}

bool SerialCore::openSerialPort(Settings s)
{
    m_serial->setPortName(s.portName);
    m_serial->setBaudRate(s.baudRate);
    m_serial->setDataBits(s.dataBits);
    m_serial->setParity(s.parity);
    m_serial->setStopBits(s.stopBits);

    if (m_serial->open(QIODevice::ReadWrite)) {
        qInfo() << "Connected";
        return true;
        // showStatusMessage(tr("Connected to %1 : %2, %3, %4, %5, %6")
        //                   .arg(s.portName).arg(s.stringBaudRate).arg(s.stringDataBits)
        //                   .arg(s.stringParity).arg(s.stringStopBits).arg(s.stringFlowControl));
    } else {
        qCritical() << "Failed to connect";
        return false;
        // QMessageBox::critical(this, tr("Error"), m_serial->errorString());
        // showStatusMessage(tr("Open error"));
    }
}

bool SerialCore::openSerialPort()
{
    return openSerialPort(m_setting);
}