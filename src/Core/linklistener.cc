#include "linklistener.h"

LinkListener::LinkListener(QObject *parent)
    : QObject(parent)
{

    _pTimer = new QTimer(this);

}

LinkListener::~LinkListener()
{
    _pTimer->stop();

    delete _pTimer;
}

void LinkListener::init()
{

    connect(_pTimer, &QTimer::timeout, this, &LinkListener::_onTimeout);

    _pTimer->start(1000);
}

void LinkListener::_onTimeout()
{

    const auto serialPortInfos = QSerialPortInfo::availablePorts();

    if(serialPortInfos.size() != _portNums)
    {
        _portNums = serialPortInfos.size();

        QVariantMap ports{};

        for(auto &port: serialPortInfos)
        {
            ports.insert(port.portName() + " - " + port.description(), port.portName());
        }

        setPorts(ports);

    }

}

void LinkListener::setPorts(const QVariantMap &ports)
{
    _ports = ports;
    emit portsChanged();
}


QVariantMap LinkListener::ports(void)
{
    return _ports;
}
