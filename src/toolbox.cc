#include "toolbox.h"

#include "QmlControls/dcpallete.h"


ToolBox* ToolBox::_instance = nullptr;


ToolBox::ToolBox(QObject *app)
    : QObject(app)
{
    _pCore = new DCCore(this);
}

ToolBox::~ToolBox()
{
    delete _pCore;
}

void ToolBox::init()
{
    QQmlEngine::setObjectOwnership(this, QQmlEngine::CppOwnership);

    qmlRegisterSingletonType<ToolBox>("ToolBox", 1, 0, "ToolBox", ToolBox::getInstance);
    qmlRegisterType<DCPallete>("DCPallete", 1, 0, "DCPallete");


    _pCore->init();
}
