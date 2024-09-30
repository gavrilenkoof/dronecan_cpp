#include "dronecancore.h"

DronecanCore::DronecanCore(QObject *parent, DronecanCore *core)
    : QObject(parent)
{
    qDebug() << "Created";
}

DronecanCore::~DronecanCore()
{
    qDebug() << "Core destroyed";
}

void DronecanCore::connect()
{
    qDebug() << "Local";
}
