#ifndef TOOLBOX_H
#define TOOLBOX_H

#include <QObject>
#include <QQmlApplicationEngine>
#include <QtQml/qqmlregistration.h>


Q_MOC_INCLUDE("linkmanager.h")
Q_MOC_INCLUDE("dcpallete.h")
Q_MOC_INCLUDE("serialcanwrap.h")


class LinkManager;
class DCPallete;
class SerialCANWrap;


class ToolBox : public QObject
{
    Q_OBJECT
public:
    Q_PROPERTY(DCPallete* pallete READ pallete CONSTANT)
    Q_PROPERTY(LinkManager* linkManager READ linkManager CONSTANT)
    Q_PROPERTY(SerialCANWrap* slcan READ slcan CONSTANT)


    LinkManager *linkManager(void)
    {
        return _pLinkManager;
    }

    DCPallete *pallete(void)
    {
        return _pPall;
    }

    SerialCANWrap *slcan(void)
    {
        return _pSlcan;
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

    QQmlApplicationEngine *getQmlEngine(void)
    {
        return _pQmlEngine;
    }

private:
    ToolBox(QObject *app = nullptr);
    ~ToolBox();

private:

    static ToolBox *_instance;

    LinkManager *_pLinkManager{nullptr};
    DCPallete *_pPall{nullptr};
    SerialCANWrap *_pSlcan{nullptr};
    QQmlApplicationEngine *_pQmlEngine{nullptr};


signals:

};

#endif // TOOLBOX_H
