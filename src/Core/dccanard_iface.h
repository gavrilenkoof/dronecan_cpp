#ifndef DCCANARD_IFACE_H
#define DCCANARD_IFACE_H

#include <queue>
#include <QDebug>

// include the canard C++ APIs
#include "canard.h"
#include "canard/publisher.h"
#include "canard/subscriber.h"
#include "canard/service_client.h"
#include "canard/service_server.h"
#include "canard/handler_list.h"
#include "canard/transfer_object.h"


class DCCanardIface : public Canard::Interface
{
public:
    DCCanardIface();
    ~DCCanardIface();

    // implement required interface functions
    bool broadcast(const Canard::Transfer &bcast_transfer) override;
    bool request(uint8_t destination_node_id, const Canard::Transfer &req_transfer) override;
    bool respond(uint8_t destination_node_id, const Canard::Transfer &res_transfer) override;
    uint8_t get_node_id() const override { return canard.node_id; }

    void init(void);

    void rxFrame(CanardCANFrame & rx_frame, uint64_t timestamp);
    void fill_tx_queue(std::queue<CanardCANFrame> &tx_queue);

private:
    static constexpr int TX_QUEUE_MAX = 200;

    static void _onTransferReceived(CanardInstance* ins, CanardRxTransfer* transfer);
    static bool _shouldAcceptTransfer(const CanardInstance* ins,
                                         uint64_t* out_data_type_signature,
                                         uint16_t data_type_id,
                                         CanardTransferType transfer_type,
                                         uint8_t source_node_id);

private:
    CanardInstance canard;
    CanardTxTransfer tx_transfer;
    uint8_t _memory_pool[8192]{};
};

#endif // DCCANARD_IFACE_H
