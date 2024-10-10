#include "serialcan.h"

SerialCAN *SerialCAN::_instance{nullptr};



SerialCAN::SerialCAN(QObject *parent)
    : QObject(parent)
{

}

SerialCAN::~SerialCAN()
{

}


void SerialCAN::init()
{

}

bool SerialCAN::tryConnect(LinkSerial *link)
{
//    QByteArray ba("Hello");

//    link->writeBytesThreadSafe(ba);

    return true;
}

void SerialCAN::onRecieveBytes(LinkSerial *link, QByteArray bytes)
{
    qDebug() << bytes;

}
