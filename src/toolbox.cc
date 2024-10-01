#include "toolbox.h"


ToolBox* ToolBox::_instance = nullptr;


ToolBox::ToolBox(QObject *app)
    : QObject(app)
{
    _pCore = new DronecanCore(this);
}

ToolBox::~ToolBox()
{
    delete _pCore;
}

void ToolBox::init()
{
//    QQmlEngine::setObjectOwnership(this, QQmlEngine::CppOwnership);
//    qmlRegisterUncreatableType<ToolsBox>("ToolsBox", 1, 0, "ToolsBox", "Reference only");

    qmlRegisterSingletonType<ToolBox>("ToolBox", 1, 0, "ToolBox", ToolBox::getInstance);


    _pCore->init();
}
