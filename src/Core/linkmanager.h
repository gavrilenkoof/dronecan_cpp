#ifndef LINKLISTENER_H
#define LINKLISTENER_H

#include <QObject>
#include <QSerialPortInfo>
#include <QTimer>

#include <QVariantMap>

#include <QDebug>


class LinkSerial;


class LinkManager : public QObject
{
    Q_OBJECT

public:

    Q_INVOKABLE void makeConnection(QString portName, int busNumber, int canBusBitrate, int adapterSpeed);

    Q_PROPERTY(QVariantMap ports READ ports WRITE setPorts NOTIFY portsChanged)

    QVariantMap ports(void);
    void setPorts(QVariantMap const &ports);


public:

    static LinkManager *getInstance(QObject *app = nullptr)
    {
        if(_instance == nullptr)
        {
            _instance = new LinkManager(app);
        }

        return _instance;
    }

    void init();
private:
    explicit LinkManager(QObject *parent = nullptr);
    ~LinkManager();

signals:

    void portsChanged();
    void createConnectionLink(QString portName, int busNumber, int canBusBitrate, int adapterSpeed);

private slots:

    void _checkNewPorts();
    void _onCreateConnectionLink(QString portName, int busNumber, int canBusBitrate, int adapterSpeed);

private:
    static LinkManager *_instance;

    QTimer *_pTimerPortsChecker{nullptr};

    int _portNums{};

    QVariantMap _ports{};

    std::unique_ptr<LinkSerial> _pLink;

};

#endif // LINKLISTENER_H
