#ifndef DCCANARD_H
#define DCCANARD_H

#include <QObject>
#include <QTimer>


#include "serialcan.h"
#include "dccanard_iface.h"



class DCCanard : public QObject
{
    Q_OBJECT
public:
    static DCCanard *getInstance(QObject *app = nullptr)
    {
        if(_instance == nullptr)
        {
            _instance = new DCCanard(app);
        }

        return _instance;
    }

    void init();

    std::queue<CanardCANFrame> &getTxFrameQueue(void)
    {
        return _tx_queue;
    }



signals:
    void canFramesTransmitReady(DCCanard * const canard);

public slots:
    void onCanFramesReceived(SerialCAN * const slcan);

private:
    explicit DCCanard(QObject *parent = nullptr);
    ~DCCanard();

    void _process(void);

private:
    static DCCanard *_instance;

    DCCanardIface *_pIface{nullptr};

    QTimer *_pTimerProcess{nullptr};

    std::queue<CanardCANFrame> _tx_queue{};


};

#endif // DCCANARD_H
