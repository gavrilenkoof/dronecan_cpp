#include "toolbox.h"

#include "QmlControls/dcpallete.h"


ToolBox* ToolBox::_instance = nullptr;


ToolBox::ToolBox(QObject *app)
    : QObject(app)
{
    QQmlEngine::setObjectOwnership(this, QQmlEngine::CppOwnership);

    _pLinkManager = LinkManager::getInstance(this);
    _pPall = DCPallete::getInstance(this);
}

ToolBox::~ToolBox()
{

}

void ToolBox::init()
{

    qmlRegisterSingletonType<ToolBox>("ToolBox", 1, 0, "ToolBox", ToolBox::getInstance);

    _pLinkManager->init();
    _pPall->init();
}
