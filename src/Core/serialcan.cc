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

    _ack_init_cmd = 0; // reset _ack_init_cmd
    _inited = false;

    QByteArray cmd;

    (void)_setEmptyCmd(cmd);
    link->writeBytesThreadSafe(cmd); // clear output parser
    link->waitForReadyRead(100); // wait for ACK (only for init!!)

    (void)_setDisableCanCmd(cmd);
    link->writeBytesThreadSafe(cmd);
    link->waitForReadyRead(100); // wait for ACK (only for init!!)

    (void)_setCanBaud(link->canBaud(), cmd);
    link->writeBytesThreadSafe(cmd);
    link->waitForReadyRead(100); // wait for ACK (only for init!!)

    (void)_setOpenChannel(cmd);
    link->writeBytesThreadSafe(cmd);
    link->waitForReadyRead(100); // wait for ACK (only for init!!)

    (void)_setClearErrorFlags(cmd);
    link->writeBytesThreadSafe(cmd);
    link->waitForReadyRead(100); // wait for ACK (only for init!!)


    if(_inited)
    {
        return true;
    }

    return false;
}


int SerialCAN::_setEmptyCmd(QByteArray &cmd)
{
    cmd.resize(1);
    return sprintf(cmd.data(), "%c", CARRIAGE_RET);
}

int SerialCAN::_setDisableCanCmd(QByteArray &cmd)
{
    cmd.resize(2);
    return sprintf(cmd.data(), "C%c", CARRIAGE_RET);
}

int SerialCAN::_setCanBaud(int speed, QByteArray &cmd)
{
    cmd.resize(3);
    int idx = 8;
    if(_baud2idx.find(speed) != _baud2idx.end())
    {
        idx = _baud2idx.at(speed);
    }

    return sprintf(cmd.data(), "S%d%c", idx, CARRIAGE_RET);
}

int SerialCAN::_setOpenChannel(QByteArray &cmd)
{
    cmd.resize(2);
    return sprintf(cmd.data(), "O%c", CARRIAGE_RET);
}

int SerialCAN::_setClearErrorFlags(QByteArray &cmd)
{
    cmd.resize(2);
    return sprintf(cmd.data(), "F%c", CARRIAGE_RET);
}

void SerialCAN::_addByte(LinkSerial *link, char const &byte)
{
    if(link == nullptr)
    {
        return;
    }

    if((byte >= 32 && byte <= 126)) // Normal printable ASCII character
    {
        if(_pos < SLCAN_BUFFER_SIZE)
        {
            _buf[_pos] = byte;
            ++_pos;
        }
        else
        {
            _pos = 0; // Buffer overrun; silently drop the data
        }
    }
    else if(byte == '\r') // End of command (SLCAN)
    {
        _buf[_pos] = '\0';
        QByteArray response;
        if(_processCommand(_buf, response))
        {
            link->writeBytesThreadSafe(response);
        }
        _pos = 0;
    }
    else
    {
        _pos = 0;
    }


}

bool SerialCAN::_processCommand(serialBuffer &cmd, QByteArray &response)
{

    // high traffic commans go first
    if(cmd[0] == 'T' || cmd[0] == 'D')
    {
//        _handleFrameDataExt();
        return true;
    }
    else if(cmd[0] == 't')
    {
//        _handleFrameDataStd();
        return true;
    }
    else if(cmd[0] == 'r' && cmd[1] <= 9)
    {
//        _handleRtrStd()
        return true;
    }
//    else if()

    // regular slcan commands
    switch (cmd[0])
    {
    case 'S':               // Set CAN bitrate
    case 'O':               // Open CAN in normal mode
    case 'L':               // Open CAN in listen-only mode
    case 'l':               // Open CAN with loopback enabled
    case 'C':               // Close CAN
    case 'M':               // Set CAN acceptance filter ID
    case 'm':               // Set CAN acceptance filter mask
    case 'U':               // Set UART baud rate, see http://www.can232.com/docs/can232_v3.pdf
    case 'Z':               // Enable/disable RX and loopback timestamping
//        return _getASCIIStatusCode(true);    // Returning success for compatibility reasons
        return true;
    case 'F':
        // _getHWSWversion();
//        _getStatusFlags();
        return true;
    case 'V':
       // _getHWSWversion();
        return true;
    case 'N':
//        _getSerialNumber();
        return true;
    default:
        break;
    }

    return false;
}

void SerialCAN::onRecieveBytes(LinkSerial *link, QByteArray bytes)
{
    if(!_inited && bytes.contains('\r'))
    {
        ++_ack_init_cmd;
    }

    if(!_inited && _ack_init_cmd >= 1)
    {
        _inited = true;
    }

    if(_inited)
    {
        for(char &byte: bytes)
        {
            _addByte(link, byte);
        }
    }


}
