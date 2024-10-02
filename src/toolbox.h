#ifndef TOOLBOX_H
#define TOOLBOX_H

#include <QObject>

#include "Core/dccore.h"

//#include "QmlControls/dcqmlcontrols.h"


class ToolBox : public QObject
{
    Q_OBJECT
public:
    Q_PROPERTY(DCCore* core READ core CONSTANT)

    static QObject *getInstance(QQmlEngine *, QJSEngine *)
    {
//        qDebug() << "Get instance";
        return _instance;
    }

    static ToolBox *getInstance(QObject *app = nullptr)
    {
        if(_instance == nullptr)
        {
            _instance = new ToolBox(app);
        }

        return _instance;
    }

    DCCore *core(void)
    {
//        qDebug() << "Get core";
        return _pCore;
    }

public:

    void init();

private:
    ToolBox(QObject *app = nullptr);
    ~ToolBox();

private:

    static ToolBox *_instance;

    DCCore *_pCore{nullptr};



signals:

};

#endif // TOOLBOX_H
