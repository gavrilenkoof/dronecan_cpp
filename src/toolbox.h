#ifndef TOOLBOX_H
#define TOOLBOX_H

#include <QObject>

#include "Core/dronecancore.h"


class ToolBox : public QObject
{
    Q_OBJECT
public:
    Q_PROPERTY(DronecanCore* core READ core CONSTANT)

    static QObject *getInstance(QQmlEngine *, QJSEngine *)
    {
        qDebug() << "Get instance";
        return _instance;
    }

    static ToolBox * instantiate(QObject *app)
    {
        if(_instance == nullptr)
        {
            _instance = new ToolBox(app);
        }

        return _instance;
    }

    DronecanCore *core(void)
    {
        qDebug() << "Get core";
        return _pCore;
    }


    void init();

private:
    ToolBox(QObject *app = nullptr);
    ~ToolBox();

private:

    static ToolBox *_instance;

    DronecanCore *_pCore{nullptr};


signals:

};

#endif // TOOLBOX_H
