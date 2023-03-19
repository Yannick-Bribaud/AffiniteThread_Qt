#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include "Objet.h"

class Controller : public QObject
{
    Q_OBJECT
public:
    explicit Controller(QObject *parent = nullptr);
    void start();

signals:

public slots:
};

#endif // CONTROLLER_H
