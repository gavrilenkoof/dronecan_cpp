#include "dronecanapp.h"

DronecanApp::DronecanApp(int &argc, char* argv[])
    : QApplication(argc, argv)
{
    _p_qmlAppEngine = new QQmlApplicationEngine(this);
}

DronecanApp::~DronecanApp()
{
    delete _p_qmlAppEngine;
}

void DronecanApp::init()
{

    const QUrl url("qrc:/qml/main.qml");
    QObject::connect(_p_qmlAppEngine, &QQmlApplicationEngine::objectCreated,
                         this, [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        }, Qt::QueuedConnection);

    _p_qmlAppEngine->load(url);
}
