#include "dccore.h"


DCCore* DCCore::_instance = nullptr;



DCCore::DCCore(QObject *parent)
    : QObject(parent)
{
    _pLinkListener = new LinkListener(this);
//    qDebug() << "Created";
}

DCCore::~DCCore()
{
    delete _pLinkListener;
}

void DCCore::tryConnect()
{
    emit makeConnection();
}

//QString DCCore::activePortName()
//{
//    return _activePortName;
//}

//void DCCore::setActivePortName(QString portName)
//{
//    _activePortName = portName;
//}

void DCCore::init()
{

    _pLinkListener->init();


    connect(this, &DCCore::makeConnection, this, &DCCore::onMakeConnection);
}

void DCCore::onMakeConnection()
{
    qDebug() << "make connection";
}
