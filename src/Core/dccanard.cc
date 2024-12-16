#include "dccanard.h"
#include "toolbox.h"


DCCanard *DCCanard::_instance{nullptr};



DCCanard::DCCanard(QObject *parent)
    : QObject(parent)
{
    _pTimer1000Hz = new QTimer(this);

}

void DCCanard::_proccess1000Hz()
{

}


void DCCanard::init()
{


    // init canard object
    canardInit(&canard,
               _memory_pool,
               sizeof(_memory_pool),
               _onTransferReceived,
               _shouldAcceptTransfer,
               this);

    canardSetLocalNodeID(&canard, 73);

    auto slcan = ToolBox::getInstance()->slcan();
    (void)connect(slcan, &SerialCAN::canFramesReceived, this, &DCCanard::onCanFramesReceived);

    (void)connect(_pTimer1000Hz, &QTimer::timeout, this, &DCCanard::_proccess1000Hz);
    _pTimer1000Hz->start(1);

}


void DCCanard::_onTransferReceived(CanardInstance* ins, CanardRxTransfer* transfer)
{
//    qDebug() << "_onTransferReceived";
}

bool DCCanard::_shouldAcceptTransfer(const CanardInstance *ins, uint64_t *out_data_type_signature, uint16_t data_type_id, CanardTransferType transfer_type, uint8_t source_node_id)
{
//    qDebug() << source_node_id;
    return false;
}



void DCCanard::onCanFramesReceived(SerialCAN *slcan)
{

    auto rx_queue = slcan->getRxFrameQueue();

    // Receiving
    const qint64 start_ms = QDateTime::currentMSecsSinceEpoch();
    while (!rx_queue.empty() && (QDateTime::currentMSecsSinceEpoch() - start_ms < 5))
    {
        CanardCANFrame rx_frame = rx_queue.front();
        rx_queue.pop();
        qint64 timestamp = QDateTime::currentMSecsSinceEpoch();
        canardHandleRxFrame(&canard, &rx_frame, static_cast<uint64_t>(timestamp));
    }

}
