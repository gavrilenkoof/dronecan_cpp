#ifndef DRONECANMAINWIN_H
#define DRONECANMAINWIN_H

#include <QObject>
#include "Core/dronecancore.h"

class DronecanMain : public QObject
{
    Q_OBJECT

public:
    explicit DronecanMain(QObject *parent = nullptr, DronecanCore *core = nullptr);
    ~DronecanMain();

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

#endif // DRONECANMAINWIN_H
