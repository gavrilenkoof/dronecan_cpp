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

    Q_PROPERTY(QColor darkWindow READ darkWindow CONSTANT)
    Q_PROPERTY(QColor text READ text CONSTANT)


    QColor darkWindow(void)
    {
        return colorMap["darkWindow"];
    }

    QColor text(void)
    {
        return colorMap["text"];
    }

public:
    explicit DCPallete(QObject *parent = nullptr);
    ~DCPallete();

private:
    void _buildColorMap();

private:
    static QMap<QString, QColor> colorMap;


signals:

};

#endif // DCPALLETE_H
