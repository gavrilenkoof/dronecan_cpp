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
