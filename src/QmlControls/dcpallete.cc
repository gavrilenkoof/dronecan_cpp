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
//    qDebug() << "Destroy";
}

void DCPallete::_buildColorMap()
{
    colorMap[QStringLiteral("window")] = QColor(QStringLiteral("#3a3a3a"));
    colorMap[QStringLiteral("text")] = QColor(QStringLiteral("#ffffff"));
    colorMap[QStringLiteral("windowBackground")] = QColor(QStringLiteral("#222222"));
    colorMap[QStringLiteral("button")] = QColor(QStringLiteral("#3a3a3a"));
    colorMap[QStringLiteral("buttonBorder")] = QColor(QStringLiteral("#222222"));
    colorMap[QStringLiteral("buttonText")] = QColor(QStringLiteral("#ffffff"));
    colorMap[QStringLiteral("buttonHighlight")] = QColor(QStringLiteral("#222222"));
    colorMap[QStringLiteral("buttonHighlightText")] = QColor(QStringLiteral("#000000"));
//    colorMap[QStringLiteral("buttonText")] = QColor(QStringLiteral("#ffffff"));

}
