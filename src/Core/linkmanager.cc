#include "linkmanager.h"

#include "linkserial.h"
#include "toolbox.h"
#include "serialcan.h"


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

void LinkManager::statusConnect()
{
    qDebug() << "status connect";
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

//    qDebug() << portName << " " << adapterSpeed;

    _pLink = std::make_unique<LinkSerial>(portName, busNumber, canBusBitrate, adapterSpeed);

    if(!_pLink)
    {
        qDebug() << "Error: Interface failed to allocate memory";
        return;
    }

    if(!_pLink->hardwareInit())
    {
        _pLink.reset();
        qDebug() << "Error: hardware init failed";
    }

    auto slcan = ToolBox::getInstance()->slcan();

    (void)connect(_pLink.get(), &LinkSerial::receiveBytes, slcan, &SerialCAN::onRecieveBytes);

    if(!slcan->tryConnect(_pLink.get()))
    {
        _pLink.reset();
        qDebug() << "Error: connect to adapter failed";
        return;
    }

    // emit signal about succesfull connect to the device
}

QVariantMap LinkManager::ports(void)
{
    return _ports;
}
