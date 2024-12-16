#include "dccanard.h"
#include "toolbox.h"


DCCanard *DCCanard::_instance{nullptr};



DCCanard::DCCanard(QObject *parent)
    : QObject(parent)
{

}



void DCCanard::init()
{

    auto slcan = ToolBox::getInstance()->slcan();
    (void)connect(slcan, &SerialCAN::canFramesReceived, this, &DCCanard::onCanFramesReceived);

}

void DCCanard::onCanFramesReceived(SerialCAN *slcan)
{

    auto rx_queue = slcan->getRxFrameQueue();

    while(!rx_queue.empty())
    {
//        rx_queue.front();
        rx_queue.pop();
    }


}
