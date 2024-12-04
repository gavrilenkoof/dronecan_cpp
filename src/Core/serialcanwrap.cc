#include "serialcanwrap.h"

SerialCANWrap *SerialCANWrap::_instance{nullptr};



SerialCANWrap::SerialCANWrap(QObject *parent)
    : QObject(parent)
{
    _slcan = new slcan::Serialcan();
}

SerialCANWrap::~SerialCANWrap()
{
    delete _slcan;
}


void SerialCANWrap::init()
{

}

bool SerialCANWrap::tryConnect(LinkSerial *link)
{

    _ack_init_cmd = 0; // reset _ack_init_cmd
    _inited = false;

    QByteArray cmd;
    cmd.resize(1);
    _slcan->setEmptyCmd(cmd.data(), cmd.size()); // clear output parser
    link->writeBytesThreadSafe(cmd);

    cmd.resize(2);
    _slcan->setDisableCanCmd(cmd.data(), cmd.size()); // disable can
    link->writeBytesThreadSafe(cmd);

    link->waitForReadyRead(30); // wait for ACK (only for init!!)

    cmd.resize(3);
    _slcan->setCanBaud(link->canBaud(), cmd.data(), cmd.size()); // set can speed
    link->writeBytesThreadSafe(cmd);

    link->waitForReadyRead(30); // wait for ACK (only for init!!)

    cmd.resize(2);
    _slcan->setOpenChannel(cmd.data(), cmd.size());
    link->writeBytesThreadSafe(cmd);

    link->waitForReadyRead(30); // wait for ACK (only for init!!)

    cmd.resize(2);
    _slcan->setClearErrorFlags(cmd.data(), cmd.size());
    link->writeBytesThreadSafe(cmd);

    if(_inited)
    {
        return true;
    }

    return false;
}

void SerialCANWrap::onRecieveBytes(LinkSerial *link, QByteArray bytes)
{
    if(!_inited && bytes.contains('\r'))
    {
        ++_ack_init_cmd;
    }

    if(!_inited && _ack_init_cmd >= 2)
    {
        _inited = true;
        qDebug() << "INITED";
    }

//    qDebug() << bytes;

}
