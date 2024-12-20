#ifndef TOOLBOX_H
#define TOOLBOX_H

#include <QObject>
#include <QQmlApplicationEngine>
#include <QtQml/qqmlregistration.h>


Q_MOC_INCLUDE("linkmanager.h")
Q_MOC_INCLUDE("dcpallete.h")
Q_MOC_INCLUDE("serialcan.h")
Q_MOC_INCLUDE("dccanard.h")


class LinkManager;
class DCPallete;
class SerialCAN;
class DCCanard;


class ToolBox : public QObject
{
    Q_OBJECT
public:
    Q_PROPERTY(DCPallete* pallete READ pallete CONSTANT)
    Q_PROPERTY(LinkManager* linkManager READ linkManager CONSTANT)
    Q_PROPERTY(SerialCAN* slcan READ slcan CONSTANT)


    LinkManager * const linkManager(void)
    {
        return _pLinkManager;
    }

    DCPallete * const pallete(void)
    {
        return _pPall;
    }

    SerialCAN * const slcan(void)
    {
        return _pSlcan;
    }

    DCCanard * const canard(void)
    {
        return _pCanard;
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
    SerialCAN *_pSlcan{nullptr};
    QQmlApplicationEngine *_pQmlEngine{nullptr};
    DCCanard *_pCanard{nullptr};


signals:

};

#endif // TOOLBOX_H
