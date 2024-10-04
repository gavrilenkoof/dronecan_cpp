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

        QList<QString> ports{};

        for(auto &port: serialPortInfos)
        {
            ports.append(port.portName());
        }

        setPorts(ports);

    }

}

void LinkListener::setPorts(const QList<QString> &ports)
{
    _ports = ports;
    emit portsChanged();
}


QStringList LinkListener::ports(void)
{
    return _ports;
}
