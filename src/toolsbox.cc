#include "toolsbox.h"


ToolsBox::ToolsBox(QObject *app)
    : QObject(app)
{
    _pCore = new DronecanCore(this);
}

ToolsBox::~ToolsBox()
{
    delete _pCore;
}

void ToolsBox::init()
{
//    QQmlEngine::setObjectOwnership(this, QQmlEngine::CppOwnership);
//    qmlRegisterUncreatableType<ToolsBox>("ToolsBox", 1, 0, "ToolsBox", "Reference only");

    _pCore->init();
}
