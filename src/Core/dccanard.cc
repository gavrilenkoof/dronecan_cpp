#include "dccanard.h"
#include "toolbox.h"


DCCanard *DCCanard::_instance{nullptr};



DCCanard::DCCanard(QObject *parent)
    : QObject(parent)
{
    _pTimerProcess = new QTimer(this);
    _pIface = new DCCanardIface();
}

DCCanard::~DCCanard()
{
    delete _pIface;
}

void DCCanard::_process()
{

    _pIface->fill_tx_queue(_tx_queue);

    if(!_tx_queue.empty())
    {
        emit canFramesTransmitReady(this);
    }

}


void DCCanard::init()
{


    _pIface->init();


    (void)connect(_pTimerProcess, &QTimer::timeout, this, &DCCanard::_process);
    _pTimerProcess->start(1);

}


void DCCanard::onCanFramesReceived(SerialCAN *slcan)
{

    auto rx_queue = slcan->getRxFrameQueue();
    // Receiving
    const qint64 start_ms = QDateTime::currentMSecsSinceEpoch();
    qint64 timestamp;
    while (!rx_queue.empty() && (QDateTime::currentMSecsSinceEpoch() - start_ms < 5))
    {
        CanardCANFrame rx_frame = rx_queue.front();
        rx_queue.pop();
        timestamp = QDateTime::currentMSecsSinceEpoch();
        _pIface->rxFrame(rx_frame, static_cast<uint64_t>(timestamp));
    }

}
