#include "dronecanmain.h"

DronecanMain::DronecanMain(QObject *parent, DronecanCore *core)
    : QObject(parent)
    , _pCore(core)
{

}

DronecanMain::~DronecanMain()
{

}
