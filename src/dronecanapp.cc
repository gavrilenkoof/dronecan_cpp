#include "dronecanapp.h"

DronecanApp::DronecanApp(int &argc, char* argv[])
    : QApplication(argc, argv)
{

}


DronecanApp::~DronecanApp()
{
    delete _pQmlEngine;
    delete _pCore;
    delete _pSetup;

    qDebug() << "App destroyed";
}

void DronecanApp::init()
{

    _pQmlEngine = new QQmlApplicationEngine(this);

    qmlRegisterUncreatableType<DronecanCore>("DronecanCore", 1, 0, "DronecanCore", "Reference only");
    qmlRegisterUncreatableType<DronecanSetup>("DronecanSetup", 1, 0, "DronecanSetup", "Reference only");

    _pCore = new DronecanCore(this);
    _pSetup = new DronecanSetup(this, _pCore);
    _pMain = new DronecanMain(this, _pCore);

    _pQmlEngine->rootContext()->setContextProperty("_setup", _pSetup);
    _pQmlEngine->rootContext()->setContextProperty("_main", _pMain);

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
