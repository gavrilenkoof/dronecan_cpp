#ifndef DRONECANCORE_H
#define DRONECANCORE_H

#include <QObject>
#include <QQmlApplicationEngine>
#include <QtQml/qqmlregistration.h>
#include <QDebug>

#include "linklistener.h"


class DCCore : public QObject
{
    Q_OBJECT

public:

    Q_INVOKABLE void tryConnect();

    Q_PROPERTY(LinkListener* link READ link CONSTANT)

public:

    static DCCore *getInstance(QObject *app = nullptr)
    {
        if(_instance == nullptr)
        {
            _instance = new DCCore(app);
        }

        return _instance;
    }

    LinkListener* link(void)
    {
        return _pLinkListener;
    }


    void init();

signals:

    void makeConnection();

private slots:

    void onMakeConnection();

private:
    explicit DCCore(QObject *parent = nullptr);
    ~DCCore();

private:
    int _id{0};

    static DCCore *_instance;

    LinkListener *_pLinkListener{nullptr};

signals:

};

#endif // DRONECANCORE_H
