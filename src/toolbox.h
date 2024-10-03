#ifndef TOOLBOX_H
#define TOOLBOX_H

#include <QObject>

#include "Core/dccore.h"
#include "QmlControls/dcpallete.h"



class ToolBox : public QObject
{
    Q_OBJECT
public:
    Q_PROPERTY(DCCore* core READ core CONSTANT)
    Q_PROPERTY(DCPallete* pallete READ pallete CONSTANT)


    DCCore *core(void)
    {
        return _pCore;
    }

    DCPallete *pallete(void)
    {
        return _pPall;
    }



public:

    static QObject *getInstance(QQmlEngine *, QJSEngine *)
    {
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

    void init();

private:
    ToolBox(QObject *app = nullptr);
    ~ToolBox();

private:

    static ToolBox *_instance;

    DCCore *_pCore{nullptr};
    DCPallete *_pPall{nullptr};


signals:

};

#endif // TOOLBOX_H
