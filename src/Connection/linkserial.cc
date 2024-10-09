#include "linkserial.h"

LinkSerial::LinkSerial(QString &portName, int &busNumber, int &canBusBitrate, int &adapterSpeed, QObject *parent)
    : QThread(parent)
    , _portName(portName)
    , _busNumber(busNumber)
    , _canBusBitrate(canBusBitrate)
    , _serialSpeed(adapterSpeed)
{
//    qDebug() << "Create";

}

LinkSerial::~LinkSerial()
{
    qDebug() << "Delete";
    if(_pPort && _pPort->isOpen())
    {
        _pPort->close();
    }

    delete _pPort;
}

bool LinkSerial::tryConnect()
{

    if(_pPort)
    {
        qDebug() << "Port is already opened!";
        return false;
    }

    _pPort = new QSerialPort(_portName, this);

    if(!_pPort)
    {
        return false;
    }

    _pPort->open(QIODevice::ReadWrite);

    if(!_pPort->isOpen())
    {
        _pPort->close();
        return false;
    }

    _pPort->setDataTerminalReady(true);
    _pPort->setBaudRate(_serialSpeed);
    _pPort->setDataBits(QSerialPort::DataBits::Data8);
    _pPort->setFlowControl(QSerialPort::FlowControl::NoFlowControl);
    _pPort->setStopBits(QSerialPort::StopBits::OneStop);
    _pPort->setParity(QSerialPort::Parity::NoParity);

    (void)connect(_pPort, &QIODevice::readyRead, this, &LinkSerial::_readBytes);
    (void)connect(_pPort, &QSerialPort::errorOccurred, this, &LinkSerial::linkError);

    return true;
}

void LinkSerial::writeBytesThreadSafe(QByteArray &bytes)
{
    if(_pPort && _pPort->isOpen())
    {
        (void)_pPort->write(bytes);
    }
}

void LinkSerial::linkError(QSerialPort::SerialPortError error)
{
    qDebug() << error;
}

void LinkSerial::_readBytes(void)
{
//    qDebug() << "Read";

    if(_pPort)
    {
        qint64 byteCount = _pPort->bytesAvailable();
        if(byteCount)
        {
            QByteArray buffer{};
            buffer.resize(byteCount);
            _pPort->read(buffer.data(), buffer.size());
            emit receiveBytes(this, buffer);
        }
    }
    else
    {
        qWarning() << "Serial port is not readable";
    }
}
