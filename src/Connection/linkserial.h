#ifndef LINKSERIAL_H
#define LINKSERIAL_H

//#include <QObject>
#include <QtCore/QThread>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

#include <QDebug>


class LinkSerial : public QThread
{
    Q_OBJECT

public:

    Q_PROPERTY(int canBaud READ canBaud CONSTANT)

    int canBaud(void)
    {
        return _canBusBitrate;
    }

public:
    LinkSerial(QString &portName, int &busNumber, int &canBusBitrate, int &adapterSpeed, QObject *parent = nullptr);
    virtual ~LinkSerial();


    bool hardwareInit(void);

    void writeBytesThreadSafe(QByteArray &data);

    void waitForReadyRead(int msec = 50);

protected:


signals:
    void receiveBytes(LinkSerial *link, QByteArray bytes);

public slots:
    void linkError(QSerialPort::SerialPortError error);

private slots:
    void _readBytes(void);
    void _writeBytes(QByteArray const &data);

private:
    QString _portName{};
    int _busNumber{};
    int _canBusBitrate{};
    int _serialSpeed{};


    QSerialPort *_pPort{nullptr};
//    QByteArray _transmitBuffer{};

};

#endif // LINKSERIAL_H
