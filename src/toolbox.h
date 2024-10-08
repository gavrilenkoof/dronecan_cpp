#ifndef TOOLBOX_H
#define TOOLBOX_H

#include <QObject>
#include <QQmlApplicationEngine>
#include <QtQml/qqmlregistration.h>

#include "Core/linkmanager.h"
#include "QmlControls/dcpallete.h"



class ToolBox : public QObject
{
    Q_OBJECT
public:
    Q_PROPERTY(DCPallete* pallete READ pallete CONSTANT)
    Q_PROPERTY(LinkManager* linkManager READ linkManager CONSTANT)


    LinkManager *linkManager(void)
    {
        return _pLinkManager;
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

    LinkManager *_pLinkManager{nullptr};
    DCPallete *_pPall{nullptr};


signals:

};

#endif // TOOLBOX_H
