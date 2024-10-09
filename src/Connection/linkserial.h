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
    LinkSerial(QString &portName, int &busNumber, int &canBusBitrate, int &adapterSpeed, QObject *parent = nullptr);
    virtual ~LinkSerial();

    bool tryConnect(void);

    void writeBytesThreadSafe(QByteArray &bytes);

protected:


signals:
    void receiveBytes(LinkSerial *link, QByteArray bytes);

public slots:
    void linkError(QSerialPort::SerialPortError error);

private slots:
    void _readBytes(void);


private:
    QString _portName{};
    int _busNumber{};
    int _canBusBitrate{};
    int _serialSpeed{};


    QSerialPort *_pPort{nullptr};
//    QByteArray _transmitBuffer{};

};

#endif // LINKSERIAL_H
