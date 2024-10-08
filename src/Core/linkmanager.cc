#include "linkmanager.h"


LinkManager* LinkManager::_instance = nullptr;


LinkManager::LinkManager(QObject *parent)
    : QObject(parent)
{

    _pTimerPortsChecker = new QTimer(this);

}

LinkManager::~LinkManager()
{
    _pTimerPortsChecker->stop();

    delete _pTimerPortsChecker;
}

void LinkManager::init()
{

    connect(this, &LinkManager::createConnectionLink, this, &LinkManager::_onCreateConnectionLink);
    connect(_pTimerPortsChecker, &QTimer::timeout, this, &LinkManager::_checkNewPorts);

    _pTimerPortsChecker->start(1000);
}

void LinkManager::_checkNewPorts()
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

void LinkManager::setPorts(const QVariantMap &ports)
{
    _ports = ports;
    emit portsChanged();
}


void LinkManager::makeConnection(QString portName, int busNumber, int canBusBitrate, int adapterSpeed)
{
    emit createConnectionLink(portName, busNumber, canBusBitrate, adapterSpeed);
}


void LinkManager::_onCreateConnectionLink(QString portName, int busNumber, int canBusBitrate, int adapterSpeed)
{
//    qDebug() << "Make connection";
    if(_pLink != nullptr)
    {
        qDebug() << "Error: port has alredy been created";
        return;
    }

    // TODO add data validator

    qDebug() << portName << " " << adapterSpeed;

    _pLink = std::make_unique<LinkSerial>(portName, busNumber, canBusBitrate, adapterSpeed);

    if(!_pLink)
    {
        qDebug() << "Error: Interface failed to allocate memory";
        return;
    }

    if(!_pLink->tryConnect())
    {
        _pLink.reset();
        qDebug() << "Error: connection failed";
    }

//    (void)connect(_pLink.get(), &LinkInterface::bytesReceived, this, &LinkManager::testBytesRecieved);

}

QVariantMap LinkManager::ports(void)
{
    return _ports;
}
