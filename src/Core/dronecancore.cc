#include "dronecancore.h"

DronecanCore::DronecanCore(QObject *parent)
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

void DronecanCore::init()
{
//    QQmlEngine::setObjectOwnership(this, QQmlEngine::CppOwnership);
//    qmlRegisterUncreatableType<DronecanCore>("DronecanCore", 1, 0, "DronecanCore", "Reference only");
}
