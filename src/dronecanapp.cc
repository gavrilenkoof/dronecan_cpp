#include "dronecanapp.h"

DronecanApp::DronecanApp(int &argc, char* argv[])
    : QApplication(argc, argv)
{

    _pTools = new ToolsBox(this);
    _pQmlEngine = new QQmlApplicationEngine(this);
}


DronecanApp::~DronecanApp()
{
//    delete _pTools;
    delete _pQmlEngine;
    qDebug() << "App destroyed";
}

void DronecanApp::init()
{

    _pTools->init();

    _pQmlEngine->rootContext()->setContextProperty("_tools", _pTools);

}

int DronecanApp::execApp()
{

    const QUrl url("qrc:/qml/main.qml");
    QObject::connect(_pQmlEngine, &QQmlApplicationEngine::objectCreated,
                         this, [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        }, Qt::QueuedConnection);

    _pQmlEngine->load(url);

    return this->exec();
}

int DronecanApp::execSetup()
{
    const QUrl url("qrc:/qml/setup.qml");
    QObject::connect(_pQmlEngine, &QQmlApplicationEngine::objectCreated,
                         this, [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        }, Qt::QueuedConnection);

    _pQmlEngine->load(url);

    return this->exec();

}
