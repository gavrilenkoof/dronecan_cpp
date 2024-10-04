#include "toolbox.h"

#include "QmlControls/dcpallete.h"


ToolBox* ToolBox::_instance = nullptr;


ToolBox::ToolBox(QObject *app)
    : QObject(app)
{
    QQmlEngine::setObjectOwnership(this, QQmlEngine::CppOwnership);

    _pCore = DCCore::getInstance(this);
    _pPall = DCPallete::getInstance(this);
}

ToolBox::~ToolBox()
{

}

void ToolBox::init()
{

    qmlRegisterSingletonType<ToolBox>("ToolBox", 1, 0, "ToolBox", ToolBox::getInstance);

    _pCore->init();
    _pPall->init();
}
