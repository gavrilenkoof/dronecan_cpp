#include "toolbox.h"

#include "linkmanager.h"
#include "dcpallete.h"
#include "serialcanwrap.h"

ToolBox* ToolBox::_instance = nullptr;


ToolBox::ToolBox(QObject *app)
    : QObject(app)
{
    QQmlEngine::setObjectOwnership(this, QQmlEngine::CppOwnership);

    _pLinkManager = LinkManager::getInstance(this);
    _pPall = DCPallete::getInstance(this);
    _pSlcan = SerialCANWrap::getInstance(this);

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
}
