#ifndef SerialCANWrap_H
#define SerialCANWrap_H

#include <QObject>
#include <QDebug>
#include <array>

#include "linkserial.h"

#include "serialcan.h"


class SerialCANWrap : public QObject
{
    Q_OBJECT
public:


public:

    static SerialCANWrap *getInstance(QObject *app = nullptr)
    {
        if(_instance == nullptr)
        {
            _instance = new SerialCANWrap(app);
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
    explicit SerialCANWrap(QObject *parent = nullptr);
    ~SerialCANWrap();
private:

    static SerialCANWrap *_instance;

    slcan::Serialcan *_slcan{nullptr};


    int _ack_init_cmd{};
    bool _inited{false};

};

#endif // SerialCANWrap_H
