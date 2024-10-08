#include "linkinterface.h"

LinkInterface::LinkInterface(QString &portName, int &busNumber, int &canBusBitrate, int &adapterSpeed, QObject *parent)
    : QThread(parent)
{
    qDebug() << "Create";
}

LinkInterface::~LinkInterface()
{
    qDebug() << "Delete";
}

bool LinkInterface::tryConnect()
{
    return false;
}
