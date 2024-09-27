#ifndef DRONECANAPP_H
#define DRONECANAPP_H

#include <QtWidgets/QApplication>
#include <QQmlApplicationEngine>


class DronecanApp : public QApplication
{
    Q_OBJECT
public:
    DronecanApp(int &argc, char* argv[]);
    ~DronecanApp();

public:
    void init();

private:
    QQmlApplicationEngine* _p_qmlAppEngine{nullptr};
};

#endif // DRONECANAPP_H
