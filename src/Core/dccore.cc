#include "dccore.h"

DCCore::DCCore(QObject *parent)
    : QObject(parent)
{

//    qDebug() << "Created";

}

DCCore::~DCCore()
{
//    qDebug() << "Core destroyed";
}

void DCCore::connect()
{
//    qDebug() << "Local";
}

void DCCore::init()
{
//    QQmlEngine::setObjectOwnership(this, QQmlEngine::CppOwnership);
//    qmlRegisterUncreatableType<DronecanCore>("DronecanCore", 1, 0, "DronecanCore", "Reference only");
}
