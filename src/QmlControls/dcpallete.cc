#include "dcpallete.h"


QMap<QString, QColor> DCPallete::colorMap{};


DCPallete::DCPallete(QObject *parent)
    : QObject(parent)
{

    if(colorMap.isEmpty())
    {
        _buildColorMap();
    }

}

DCPallete::~DCPallete()
{
    qDebug() << "Destroy";
}

void DCPallete::_buildColorMap()
{
    colorMap[QStringLiteral("darkWindow")] = QColor(QStringLiteral("#3a3a3a"));
    colorMap[QStringLiteral("text")] = QColor(QStringLiteral("#ffffff"));
}
