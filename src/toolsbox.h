#ifndef TOOLBOX_H
#define TOOLBOX_H

#include <QObject>

#include "Core/dronecancore.h"


class ToolsBox : public QObject
{
    Q_OBJECT
public:
    ToolsBox(QObject *app);
    ~ToolsBox();

    Q_PROPERTY(DronecanCore* core READ core CONSTANT)

    DronecanCore *core(void)
    {
        return _pCore;
    }


    void init();


private:

    DronecanCore *_pCore{nullptr};


signals:

};

#endif // TOOLBOX_H
