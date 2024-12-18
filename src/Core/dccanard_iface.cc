#include "dccanard_iface.h"

DCCanardIface::DCCanardIface()
    : Interface(0)
{

}

DCCanardIface::~DCCanardIface()
{

}

void DCCanardIface::init()
{
    //     init canard object
    canardInit(&canard,
                _memory_pool,
                sizeof(_memory_pool),
                _onTransferReceived,
                _shouldAcceptTransfer,
                this);

    canardSetLocalNodeID(&canard, 73);

}

void DCCanardIface::rxFrame(CanardCANFrame &rx_frame, uint64_t timestamp)
{
    canardHandleRxFrame(&canard, &rx_frame, timestamp);
}

void DCCanardIface::fill_tx_queue(std::queue<CanardCANFrame> &tx_queue)
{

    CanardCANFrame frame{};
    for (const CanardCANFrame* txf = NULL; (txf = canardPeekTxQueue(&canard)) != NULL;)
    {
        frame.id = txf->id;
        frame.data_len = txf->data_len;
        frame.iface_id = txf->iface_id;
        memcpy(frame.data, txf->data, frame.data_len);
        tx_queue.push(frame);
        canardPopTxQueue(&canard);

        if(tx_queue.size() >= TX_QUEUE_MAX)
        {
            break;
        }

    }
}


bool DCCanardIface::broadcast(const Canard::Transfer &bcast_transfer)
{
    tx_transfer = {
        .transfer_type = bcast_transfer.transfer_type,
        .data_type_signature = bcast_transfer.data_type_signature,
        .data_type_id = bcast_transfer.data_type_id,
        .inout_transfer_id = bcast_transfer.inout_transfer_id,
        .priority = bcast_transfer.priority,
        .payload = (const uint8_t*)bcast_transfer.payload,
        .payload_len = uint16_t(bcast_transfer.payload_len),
#if CANARD_ENABLE_CANFD
        .canfd = bcast_transfer.canfd,
#endif
#if CANARD_ENABLE_DEADLINE
        .deadline_usec = micros64() + (bcast_transfer.timeout_ms * 1000),
#endif
#if CANARD_MULTI_IFACE
        .iface_mask = uint8_t((1<<num_ifaces) - 1),
#endif
    };
    // do canard broadcast
    bool success = canardBroadcastObj(&canard, &tx_transfer) > 0;
    return success;
}


bool DCCanardIface::request(uint8_t destination_node_id, const Canard::Transfer &req_transfer)
{
    tx_transfer = {
        .transfer_type = req_transfer.transfer_type,
        .data_type_signature = req_transfer.data_type_signature,
        .data_type_id = req_transfer.data_type_id,
        .inout_transfer_id = req_transfer.inout_transfer_id,
        .priority = req_transfer.priority,
        .payload = (const uint8_t*)req_transfer.payload,
        .payload_len = uint16_t(req_transfer.payload_len),
#if CANARD_ENABLE_CANFD
        .canfd = req_transfer.canfd,
#endif
#if CANARD_ENABLE_DEADLINE
        .deadline_usec = micros64() + (req_transfer.timeout_ms * 1000),
#endif
#if CANARD_MULTI_IFACE
        .iface_mask = uint8_t((1<<num_ifaces) - 1),
#endif
    };
    // do canard request
    return canardRequestOrRespondObj(&canard, destination_node_id, &tx_transfer) > 0;
}


bool DCCanardIface::respond(uint8_t destination_node_id, const Canard::Transfer &res_transfer)
{
    tx_transfer = {
        .transfer_type = res_transfer.transfer_type,
        .data_type_signature = res_transfer.data_type_signature,
        .data_type_id = res_transfer.data_type_id,
        .inout_transfer_id = res_transfer.inout_transfer_id,
        .priority = res_transfer.priority,
        .payload = (const uint8_t*)res_transfer.payload,
        .payload_len = uint16_t(res_transfer.payload_len),
#if CANARD_ENABLE_CANFD
        .canfd = res_transfer.canfd,
#endif
#if CANARD_ENABLE_DEADLINE
        .deadline_usec = micros64() + (res_transfer.timeout_ms * 1000),
#endif
#if CANARD_MULTI_IFACE
        .iface_mask = uint8_t((1<<num_ifaces) - 1),
#endif
    };
    // do canard respond
    return canardRequestOrRespondObj(&canard, destination_node_id, &tx_transfer) > 0;
}


void DCCanardIface::_onTransferReceived(CanardInstance* ins, CanardRxTransfer* transfer)
{
//    qDebug() << transfer->data_type_id;
}

bool DCCanardIface::_shouldAcceptTransfer(const CanardInstance *ins, uint64_t *out_data_type_signature, uint16_t data_type_id, CanardTransferType transfer_type, uint8_t source_node_id)
{
//    qDebug() << source_node_id;
    return true;
}
