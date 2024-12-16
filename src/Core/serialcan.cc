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
//

    // high traffic commans go first
    if(cmd[0] == 'T' || cmd[0] == 'D')
    {
//        qDebug() << cmd.data();
        bool status = _handleFrameDataExt(cmd, cmd[0] == 'D');
        response.resize(5);
        if(status)
        {
            snprintf(response.data(), 3, "Z%c", CARRIAGE_RET);
        }
        else
        {
            snprintf(response.data(), 2, "%c", A_SYBMOL);
        }
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
        response.resize(3);
        snprintf(response.data(), 2, "%c", _getASCIIStatusCode(true));
        return true;
    case 'F':               // Get status flags
        response.resize(4);
        snprintf(response.data(), 4, "F%d%c", _getStatusFlags(), CARRIAGE_RET);
        return true;
    case 'V':               // HW/SW version
       response.resize(7);
       snprintf(response.data(), 7, "V%x%x%x%x%c", 1, 0, 1, 0, CARRIAGE_RET);
       return true;
    case 'N':
        response.resize(10);
        snprintf(response.data(), 10, "N%s%c", _getSerialNumber().toStdString().data(), CARRIAGE_RET);
        return true;
    default:
        break;
    }

    response.resize(3);
    snprintf(response.data(), 2, "%c", _getASCIIStatusCode(false));

    return true;
}

char SerialCAN::_getASCIIStatusCode(bool status)
{
    return status ? '\r' : '\a';
}

char SerialCAN::_getStatusFlags()
{
    return 0; // Returning success for compatibility reasons
}

QString SerialCAN::_getSerialNumber()
{
    return QString("1.0");
}

bool SerialCAN::_handleFrameDataExt(serialBuffer &cmd, bool canfd)
{

    CANFrame f{};
    bool hex2nibble_error{false};

    f.canfd = canfd;
    f.id = f.FlagEFF |
            (hex2nibble(cmd[1], hex2nibble_error) << 28) |
            (hex2nibble(cmd[2], hex2nibble_error) << 24) |
            (hex2nibble(cmd[3], hex2nibble_error) << 20) |
            (hex2nibble(cmd[4], hex2nibble_error) << 16) |
            (hex2nibble(cmd[5], hex2nibble_error) << 12) |
            (hex2nibble(cmd[6], hex2nibble_error) << 8) |
            (hex2nibble(cmd[7], hex2nibble_error) << 4) |
            (hex2nibble(cmd[8], hex2nibble_error) << 0);

    f.dlc = hex2nibble(cmd[9], hex2nibble_error);

    if (hex2nibble_error || f.dlc > (canfd ? 15 : 8))
    {
        return false;
    }

    const char *p = &cmd[10];
    const uint8_t dlen = CANFrame::dataLengthToDlc(f.dlc);
    for(uint8_t i = 0; i < dlen; ++i)
    {
        f.data[i] = (hex2nibble(*p, hex2nibble_error) << 4) | hex2nibble(*(p + 1), hex2nibble_error);
        p += 2;
    }



    if(hex2nibble_error)
    {
        return false;
    }

//    qDebug() << f.data[0] << f.data[1] << f.data[2];

    CanardCANFrame frame{};
    frame.id = f.id;
    frame.data_len = f.dlc;
    frame.iface_id = 0;
    memcpy(frame.data, f.data, frame.data_len);

    _rx_queue.push(frame);

    return true;
}

uint8_t SerialCAN::hex2nibble(char c, bool &hex2nibble_error)
{
    // Must go into RAM, not flash, because flash is slow
    static uint8_t NumConversionTable[] = {
        0, 1, 2, 3, 4, 5, 6, 7, 8, 9
    };

    static uint8_t AlphaConversionTable[] = {
        10, 11, 12, 13, 14, 15
    };

    uint8_t out = 255;

    if (c >= '0' && c <= '9') {
        out = NumConversionTable[int(c) - int('0')];
    } else if (c >= 'a' && c <= 'f') {
        out = AlphaConversionTable[int(c) - int('a')];
    } else if (c >= 'A' && c <= 'F') {
        out = AlphaConversionTable[int(c) - int('A')];
    }

    if (out == 255) {
        hex2nibble_error = true;
    }
    return out;
}

void SerialCAN::onRecieveBytes(LinkSerial *link, QByteArray bytes)
{
//    qDebug() << bytes;

    if(!_inited && bytes.contains('\r'))
    {
        ++_ack_init_cmd;
    }

    if(!_inited && _ack_init_cmd >= ACK_TO_INIT)
    {
        _inited = true;
    }

    if(_inited)
    {
        for(char &byte: bytes)
        {
            _addByte(link, byte);

            if(_rx_queue.size() >= RX_QUEUE_MAX)
            {
                break;
            }

        }

        if(!_rx_queue.empty())
        {
            emit canFramesReceived(this);
        }


    }


}
