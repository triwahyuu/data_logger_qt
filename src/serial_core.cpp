#include "serial_core.h"

#include <QTime>
#include <QDebug>

SerialCore::SerialCore(QObject *parent) : QObject(parent)
{
    m_serial = new QSerialPort();
    connect(m_serial, static_cast<void (QSerialPort::*)(QSerialPort::SerialPortError)>(&QSerialPort::error),
            this, &SerialCore::handleError);
}

SerialCore::~SerialCore()
{
}

bool SerialCore::open(SerialCore::Settings s)
{
    m_serial->setPortName(s.portName);
    m_serial->setBaudRate(s.baudRate);
    m_serial->setDataBits(s.dataBits);
    m_serial->setParity(s.parity);
    m_serial->setStopBits(s.stopBits);

    if (m_serial->open(QIODevice::ReadWrite)) {
        qInfo() << "Connected";
        m_opened = true;
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

bool SerialCore::open()
{
    return open(m_setting);
}

void SerialCore::close()
{
    if (m_serial->isOpen()){
        m_serial->close();
        m_opened = false;
    }
}

void SerialCore::handleError(QSerialPort::SerialPortError error)
{
    if (error == QSerialPort::ResourceError) {
        qCritical() << "Critical Error " << m_serial->errorString();
        close();
    }
}

void SerialCore::write(const QByteArray &data)
{
    m_serial->write(data);
}

QByteArray SerialCore::read()
{
    return m_serial->readAll();
}

bool SerialCore::isOpened()
{
    return m_opened;
}

void SerialCore::saveSetting(SerialCore::Settings s)
{
    m_setting.portName = s.portName;
    m_setting.baudRate = s.baudRate;
    m_setting.dataBits = s.dataBits;
    m_setting.parity = s.parity;
    m_setting.stopBits = s.stopBits;
    m_setting.flowControl = s.flowControl;
}
