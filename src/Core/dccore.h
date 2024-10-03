#ifndef DRONECANCORE_H
#define DRONECANCORE_H

#include <QObject>
#include <QQmlApplicationEngine>
#include <QtQml/qqmlregistration.h>
#include <QDebug>

class DCCore : public QObject
{
    Q_OBJECT

public:

    Q_PROPERTY(int id READ id WRITE setId)

    Q_INVOKABLE void tryConnect();

    void setId(int id)
    {
        qDebug() << "set id";
        _id = id;
    }

    int id(void)
    {
        return _id;
    }
public:

    static DCCore *getInstance(QObject *app = nullptr)
    {
        if(_instance == nullptr)
        {
            _instance = new DCCore(app);
        }

        return _instance;
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

signals:

};

#endif // DRONECANCORE_H
