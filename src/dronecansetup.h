#ifndef DRONECANSETUP_H
#define DRONECANSETUP_H

#include <QObject>
#include "Core/dronecancore.h"

class DronecanSetup : public QObject
{
    Q_OBJECT

public:
    explicit DronecanSetup(QObject *parent = nullptr, DronecanCore *core = nullptr);
    ~DronecanSetup();

    Q_PROPERTY(DronecanCore* core READ core CONSTANT)

public:

    DronecanCore *core(void)
    {
        return _pCore;
    }

private:
    DronecanCore *_pCore{nullptr};

signals:

};

#endif // DRONECANSETUP_H
