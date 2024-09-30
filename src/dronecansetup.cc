#include "dronecansetup.h"

DronecanSetup::DronecanSetup(QObject *parent, DronecanCore *core)
    : QObject(parent)
    , _pCore(core)
{

}

DronecanSetup::~DronecanSetup()
{
    qDebug() << "Setup destroyed";
}
