#include "dccore.h"


DCCore* DCCore::_instance = nullptr;



DCCore::DCCore(QObject *parent)
    : QObject(parent)
{

    qDebug() << "Created";

}

DCCore::~DCCore()
{

}

void DCCore::tryConnect()
{
    emit makeConnection();
}

void DCCore::init()
{
    connect(this, &DCCore::makeConnection, this, &DCCore::onMakeConnection);
}

void DCCore::onMakeConnection()
{
    qDebug() << "make connection";
}
