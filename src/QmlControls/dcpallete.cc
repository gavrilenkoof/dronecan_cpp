#include "dcpallete.h"


QMap<QString, QColor> DCPallete::colorMap{};
DCPallete *DCPallete::_instance{nullptr};


void DCPallete::init()
{
    if(colorMap.isEmpty())
    {
        _buildColorMap();
    }
}

DCPallete::DCPallete(QObject *parent)
    : QObject(parent)
{
}

DCPallete::~DCPallete()
{
    qDebug() << "Destroy";
}

void DCPallete::_buildColorMap()
{
    colorMap[QStringLiteral("window")] = QColor(QStringLiteral("#3a3a3a"));
    colorMap[QStringLiteral("text")] = QColor(QStringLiteral("#ffffff"));
    colorMap[QStringLiteral("windowBackground")] = QColor(QStringLiteral("#222222"));
}
