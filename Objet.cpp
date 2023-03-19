#include "Objet.h"
#include <QDebug>
#include <QTimer>

Objet::Objet(QObject *parent) : QObject(parent){}


void Objet::debugObjetFiable() const {
    //L'appel a été fait par un branchement, il s'exécute dans le thread de l'appelant
    //On force l'exécution de la fonction debugObjet() dans notre run-loop
    //signature fnct: delaisMS, objet cible, Methamethode
    QTimer::singleShot(0, this, SLOT(debugObjet()));
}

void Objet::debugObjet() const {
    qDebug() << "Objet " << objectName();
    qDebug() << "   Adresse : @" << this;
    qDebug() << "   Thread id : " << thread()->currentThreadId();
    qDebug() << "";
}
