#ifndef DCPALLETE_H
#define DCPALLETE_H

#include <QObject>
#include <QtQml/qqmlregistration.h>

#include <QDebug>

#include <QColor>
#include <QMap>
#include <QString>



class DCPallete : public QObject
{
    Q_OBJECT
    QML_ELEMENT
public:

    Q_PROPERTY(QColor window READ window CONSTANT)
    Q_PROPERTY(QColor text READ text CONSTANT)
    Q_PROPERTY(QColor windowBackground READ windowBackground CONSTANT)
    Q_PROPERTY(QColor button READ button CONSTANT)
    Q_PROPERTY(QColor buttonBorder READ buttonBorder CONSTANT)
    Q_PROPERTY(QColor buttonText READ buttonText CONSTANT)
    Q_PROPERTY(QColor buttonHighlight READ buttonHighlight CONSTANT)
    Q_PROPERTY(QColor buttonHighlightText READ buttonHighlightText CONSTANT)


    QColor window(void)
    {
        return colorMap["window"];
    }

    QColor text(void)
    {
        return colorMap["text"];
    }

    QColor windowBackground(void)
    {
        return colorMap["windowBackground"];
    }

    QColor button(void)
    {
        return colorMap["button"];
    }

    QColor buttonBorder(void)
    {
        return colorMap["buttonBorder"];
    }

    QColor buttonText(void)
    {
        return colorMap["buttonText"];
    }

    QColor buttonHighlight(void)
    {
        return colorMap["buttonHighlight"];
    }

    QColor buttonHighlightText(void)
    {
        return colorMap["buttonHighlightText"];
    }

public:


    static DCPallete *getInstance(QObject *app = nullptr)
    {
        if(_instance == nullptr)
        {
            _instance = new DCPallete(app);
        }

        return _instance;
    }



    void init();


private:
    explicit DCPallete(QObject *parent = nullptr);
    ~DCPallete();

    void _buildColorMap();

private:
    static QMap<QString, QColor> colorMap;

    static DCPallete *_instance;


signals:

};

#endif // DCPALLETE_H
