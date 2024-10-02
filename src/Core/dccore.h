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

    Q_INVOKABLE void connect();

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
    explicit DCCore(QObject *parent = nullptr);
    ~DCCore();

    void init();

private:
    int _id{0};

signals:

};

#endif // DRONECANCORE_H
