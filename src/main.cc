//#include <QGuiApplication>
//#include <QQmlApplicationEngine>

#include "dronecanapp.h"


int main(int argc, char *argv[])
{

    DronecanApp app(argc, argv);

    app.init();

    auto exit_code = app.exec();

    return exit_code;
}

