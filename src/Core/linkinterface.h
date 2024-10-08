#ifndef LINKINTERFACE_H
#define LINKINTERFACE_H

//#include <QObject>
#include <QtCore/QThread>

#include <QDebug>


class LinkInterface : public QThread
{
    Q_OBJECT
public:
    explicit LinkInterface(QString &portName, int &busNumber, int &canBusBitrate, int &adapterSpeed, QObject *parent = nullptr);
    ~LinkInterface();

    bool tryConnect(void);

signals:

};

#endif // LINKINTERFACE_H
