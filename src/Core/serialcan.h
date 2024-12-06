#ifndef SerialCAN_H
#define SerialCAN_H

#include <QObject>
#include <QDebug>
#include <array>
#include <utility>

#include "linkserial.h"



class SerialCAN : public QObject
{
    Q_OBJECT
public:


public:

    static SerialCAN *getInstance(QObject *app = nullptr)
    {
        if(_instance == nullptr)
        {
            _instance = new SerialCAN(app);
        }

        return _instance;
    }

    void init();

    bool tryConnect(LinkSerial *link);

signals:
    void statusConnect();

public slots:
    void onRecieveBytes(LinkSerial *link, QByteArray bytes);


private:
    explicit SerialCAN(QObject *parent = nullptr);
    ~SerialCAN();

private:
    static constexpr char CARRIAGE_RET = '\r';
    static constexpr int SLCAN_BUFFER_SIZE = 200;

    typedef std::array<char, SLCAN_BUFFER_SIZE> serialBuffer;

private:
    int _setEmptyCmd(QByteArray &cmd);
    int _setDisableCanCmd(QByteArray &cmd);
    int _setCanBaud(int speed, QByteArray &cmd);
    int _setOpenChannel(QByteArray &cmd);
    int _setClearErrorFlags(QByteArray &cmd);
    void _addByte(LinkSerial *link, char const &byte);
//    QByteArray _processCommand(serialBuffer &cmd);
    bool _processCommand(serialBuffer &cmd, QByteArray &response);

private:

    static SerialCAN *_instance;


    int _ack_init_cmd{};
    bool _inited{false};


    std::unordered_map<int, int> const _baud2idx{
        {1000000, 8},
        {800000, 7},
        {500000, 6},
        {250000, 5},
        {125000, 4},
        {100000, 3},
        {50000, 2},
        {20000, 1},
        {10000, 0}
    };


    int _pos{0};
    serialBuffer _buf{};


};

#endif // SerialCAN_H
