#ifndef LINKLISTENER_H
#define LINKLISTENER_H

#include <QObject>
#include <QSerialPortInfo>
#include <QTimer>


//#include <QVariantList>
//#include <QMap>
//#include <QString>
#include <QVariantMap>
#include <QList>


#include <QDebug>



class LinkListener : public QObject
{
    Q_OBJECT

public:

    Q_PROPERTY(QVariantMap ports READ ports WRITE setPorts NOTIFY portsChanged)

    QVariantMap ports();
    void setPorts(QVariantMap const &ports);


public:
    explicit LinkListener(QObject *parent = nullptr);
    ~LinkListener();

    void init();
signals:

    void portsChanged();

private slots:

    void _onTimeout();

private:

    QTimer *_pTimer{nullptr};

    int _portNums{};

    QVariantMap _ports{};

};

#endif // LINKLISTENER_H
