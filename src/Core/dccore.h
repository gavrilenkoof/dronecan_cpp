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

    Q_PROPERTY(LinkListener* linkListener READ linkListener CONSTANT)
//    Q_PROPERTY(QString activePortName READ activePortName WRITE setActivePortName NOTIFY activePortNameChanged)

//    QString activePortName(void);
//    void setActivePortName(QString portName);

public:

    static DCCore *getInstance(QObject *app = nullptr)
    {
        if(_instance == nullptr)
        {
            _instance = new DCCore(app);
        }

        return _instance;
    }

    LinkListener* linkListener(void)
    {
        return _pLinkListener;
    }


    void init();

signals:

    void makeConnection();
    void activePortNameChanged();

private slots:

    void onMakeConnection();

private:
    explicit DCCore(QObject *parent = nullptr);
    ~DCCore();

private:
    static DCCore *_instance;

    LinkListener *_pLinkListener{nullptr};

//    QString _activePortName{};

signals:

};

#endif // DRONECANCORE_H
