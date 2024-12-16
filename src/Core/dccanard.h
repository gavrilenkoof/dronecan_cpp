#ifndef DCCANARD_H
#define DCCANARD_H

#include <QObject>

#include "canard.h"


class DCCanard : public QObject
{
    Q_OBJECT
public:
    explicit DCCanard(QObject *parent = nullptr);

signals:

};

#endif // DCCANARD_H
