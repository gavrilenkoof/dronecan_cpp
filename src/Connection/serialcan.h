#ifndef SERIALCAN_H
#define SERIALCAN_H

#include <QObject>
#include <QDebug>

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

    bool sendTest(LinkSerial *link);

signals:

public slots:
    void onRecieveBytes(LinkSerial *link, QByteArray bytes);


private:
    explicit SerialCAN(QObject *parent = nullptr);
    ~SerialCAN();
private:
    static SerialCAN *_instance;

};

#endif // SERIALCAN_H
