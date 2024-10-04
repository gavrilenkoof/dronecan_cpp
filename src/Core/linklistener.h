#ifndef LINKLISTENER_H
#define LINKLISTENER_H

#include <QObject>
#include <QSerialPortInfo>
#include <QTimer>
#include <QVariantList>
#include <QMap>

#include <QDebug>



class LinkListener : public QObject
{
    Q_OBJECT

public:

    Q_PROPERTY(QStringList ports READ ports WRITE setPorts NOTIFY portsChanged)

    QStringList ports(void);
    void setPorts(QStringList const &ports);


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

    QStringList _ports{};
};

#endif // LINKLISTENER_H
