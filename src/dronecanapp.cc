#include "dronecanapp.h"

DronecanApp::DronecanApp(int &argc, char* argv[])
    : QApplication(argc, argv)
{

    _pTools = ToolBox::getInstance(this);

}


DronecanApp::~DronecanApp()
{
//    delete _pQmlEngine;
//    qDebug() << "App destroyed";
}

void DronecanApp::init()
{

    _pTools->init();

}

int DronecanApp::execApp()
{


    const QUrl url("qrc:/qml/main.qml");
    QObject::connect(_pTools->getQmlEngine(), &QQmlApplicationEngine::objectCreated,
                         this, [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        }, Qt::QueuedConnection);

    _pTools->getQmlEngine()->load(url);



    return this->exec();
}

int DronecanApp::execSetup()
{
    const QUrl url("qrc:/qml/setup.qml");
    QObject::connect(_pTools->getQmlEngine(), &QQmlApplicationEngine::objectCreated,
                         this, [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        }, Qt::QueuedConnection);

    _pTools->getQmlEngine()->load(url);

    return this->exec();

}
