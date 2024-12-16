#ifndef DCCANARD_H
#define DCCANARD_H

#include <QObject>

#include "canard.h"
#include "serialcan.h"



class DCCanard : public QObject
{
    Q_OBJECT
public:
    static DCCanard *getInstance(QObject *app = nullptr)
    {
        if(_instance == nullptr)
        {
            _instance = new DCCanard(app);
        }

        return _instance;
    }

    void init();

signals:

private slots:
    void onCanFramesReceived(SerialCAN * const slcan);

private:
    explicit DCCanard(QObject *parent = nullptr);

private:
    static DCCanard *_instance;

};

#endif // DCCANARD_H
