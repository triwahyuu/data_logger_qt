#ifndef SERIAL_CORE_H
#define SERIAL_CORE_H

#include <QSerialPort>

class SerialCore : public QObject
{
    Q_OBJECT

public:
    explicit SerialCore(QObject *parent = nullptr);
    ~SerialCore();

    struct Settings {
        QString portName;
        uint32_t baudRate;
        QString stringBaudRate;
        QSerialPort::DataBits dataBits;
        QString stringDataBits;
        QSerialPort::Parity parity;
        QString stringParity;
        QSerialPort::StopBits stopBits;
        QString stringStopBits;
        QSerialPort::FlowControl flowControl;
        QString stringFlowControl;
        bool localEchoEnabled;
    };

    bool openSerialPort(Settings s);
    bool openSerialPort();
    void closeSerialPort();
    void handleError(QSerialPort::SerialPortError error);

    void saveSetting(Settings s);

private:
    QSerialPort *m_serial;
    Settings m_setting;
    bool m_opened = false;
};

#endif // SERIAL_CORE_H