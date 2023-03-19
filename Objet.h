#ifndef OBJET_H
#define OBJET_H

#include <QObject>
#include <QThread>

class Objet : public QObject
{
    Q_OBJECT
public:
    explicit Objet(QObject *parent = nullptr);
    void debugObjetFiable() const;

public slots:
    void debugObjet() const;

};

#endif // OBJET_H
