#include "toolbox.h"

#include "linkmanager.h"
#include "dcpallete.h"
#include "serialcan.h"
#include "dccanard.h"

ToolBox* ToolBox::_instance = nullptr;


ToolBox::ToolBox(QObject *app)
    : QObject(app)
{
    QQmlEngine::setObjectOwnership(this, QQmlEngine::CppOwnership);

    _pLinkManager = LinkManager::getInstance(this);
    _pPall = DCPallete::getInstance(this);
    _pSlcan = SerialCAN::getInstance(this);
    _pCanard = DCCanard::getInstance(this);

    _pQmlEngine = new QQmlApplicationEngine(this);
}

ToolBox::~ToolBox()
{
    delete _pQmlEngine;
}

void ToolBox::init()
{
    _pQmlEngine->addImportPath("qrc:/qml");
    qmlRegisterSingletonType<ToolBox>("ToolBox", 1, 0, "ToolBox", ToolBox::getInstance);

    _pLinkManager->init();
    _pPall->init();
    _pSlcan->init();
    _pCanard->init();

    // handle rx frames
    (void)connect(_pSlcan, &SerialCAN::canFramesReceived, _pCanard, &DCCanard::onCanFramesReceived);
    // handle tx frames
    (void)connect(_pCanard, &DCCanard::canFramesTransmitReady, _pSlcan, &SerialCAN::onCanFramesTransmitReady);
}
