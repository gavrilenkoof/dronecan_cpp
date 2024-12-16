#ifndef DCCANARD_H
#define DCCANARD_H

#include <QObject>
#include <QTimer>


#include "serialcan.h"



// include the canard C++ APIs
#include "canard.h"
//#include <canard/publisher.h>
#include "canard/publisher.h"
#include "canard/subscriber.h"
#include "canard/service_client.h"
#include "canard/service_server.h"
#include "canard/handler_list.h"
#include "canard/transfer_object.h"



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

signals:

private slots:
    void onCanFramesReceived(SerialCAN * const slcan);

private:
    explicit DCCanard(QObject *parent = nullptr);

    void _proccess1000Hz();
    static void _onTransferReceived(CanardInstance* ins, CanardRxTransfer* transfer);
    static bool _shouldAcceptTransfer(const CanardInstance* ins,
                                     uint64_t* out_data_type_signature,
                                     uint16_t data_type_id,
                                     CanardTransferType transfer_type,
                                     uint8_t source_node_id);

private:
    static DCCanard *_instance;

    CanardInstance canard;

    QTimer *_pTimer1000Hz{nullptr};

    uint8_t _memory_pool[8192]{};

};

#endif // DCCANARD_H
