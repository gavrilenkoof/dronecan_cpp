#ifndef DRONECANCORE_H
#define DRONECANCORE_H

#include <QObject>

#include <QDebug>

class DronecanCore : public QObject
{
    Q_OBJECT
public:
    explicit DronecanCore(QObject *parent = nullptr, DronecanCore *core = nullptr);
    ~DronecanCore();
public:

    Q_PROPERTY(int id READ id WRITE setId)

    Q_INVOKABLE void connect();

    void setId(int id)
    {
        _id = id;
    }

    int id(void)
    {
        return _id;
    }

private:
    int _id{0};

signals:

};

#endif // DRONECANCORE_H
