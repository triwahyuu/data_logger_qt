#ifndef SERIAL_CORE_H
#define SERIAL_CORE_H

#include <QSerialPort>

class SerialCore : public QObject
{
    Q_OBJECT

public:
    explicit SerialCore(QObject *parent = nullptr);
    ~SerialCore();

    typedef struct SerialSettings {
        QString portName;
        QSerialPort::BaudRate baudRate;
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
    } Settings;

    typedef struct SerialPortInfo{
        QString description;
        QString manufacturer;
        QString serialNumber;
    } PortInfo;

    bool open(Settings s);
    bool open();
    void close();
    void handleError(QSerialPort::SerialPortError error);
    bool isOpened();

    void write(const QByteArray &data);
    QByteArray read();

    void saveSetting(Settings s);
    

private:
    QSerialPort *m_serial;
    Settings m_setting;
    bool m_opened = false;
};

#endif // SERIAL_CORE_H