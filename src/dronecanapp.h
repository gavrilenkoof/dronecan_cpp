#ifndef DRONECANMAIN_H
#define DRONECANMAIN_H


#include <QtWidgets/QApplication>
#include <QQmlApplicationEngine>
#include <QtQml/qqmlregistration.h>
#include <QtQml/QQmlContext>

#include "toolbox.h"


class DronecanApp : public QApplication
{
    Q_OBJECT
public:
    explicit DronecanApp(int &argc, char* argv[]);
    ~DronecanApp();

public:
    void init();
    int execApp();

signals:


private:

    ToolBox *_pTools{nullptr};

//    DronecanCore *_pCore{nullptr};
};

#endif // DRONECANMAIN_H
