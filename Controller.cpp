#include "Controller.h"
#include <QThread>
#include <QDebug>
#include <QTimer>

Controller::Controller(QObject *parent) : QObject(parent)
{
    qDebug() << "*** 1 - Constructeur de Controller...";
    qDebug() << "   ID du thread du contrôleur : " << thread()->currentThreadId();
    qDebug() << "";
}

void Controller::start()
{
    qDebug() << "*** 2 - Controller::start...";
    qDebug() << "   ID du thread du contrôleur : " << thread()->currentThreadId();
    qDebug() << "";

    qDebug() << "*** Instanciation de l'objet o1";
    Objet *o1 = new Objet(this);
    o1->setObjectName("o1");    
    qDebug() << "   ID du thread de l'objet o1 : " << o1->thread()->currentThreadId();
    qDebug() << "";

    QThread *t2 = new QThread(this);
    t2->setObjectName("t2");
    t2->start();
    qDebug() << "*** 3 - Création du thread t2";
    qDebug() << "   ID du thread t2 : " << t2->thread()->currentThreadId();
    qDebug() << "";

    qDebug() << "*** 4 - Instanciation de l'objet o2";
    Objet *o2 = new Objet;
    o2->setObjectName("o2");    
    qDebug() << "Objet " << o2->objectName();
    qDebug() << "   Adresse : @" << o2;
    qDebug() << "   Thread id : " << o2->thread()->currentThreadId();
    qDebug() << "";

    qDebug() << "*** 5 -> Changement de l'affinité de l'objet o2";
    o2->moveToThread(t2);

    qDebug() << "*** 6 -> ID du thread de l'objet o2 : " << o2->thread()->currentThreadId();
    qDebug() << "";

    qDebug() << "*** 7 -> Appel de la fonction debugObjet()";
    o2->debugObjet();
    // L'affinité de thread de l'objet o2 semble n'avoir pas été changée...


    QTimer::singleShot(0, o2, [=]{
        qDebug() << "*** 8 -> ID du thread de l'objet o2 en passant par un signal : " << o2->thread()->currentThreadId();
        qDebug() << "";
        // L'affinité de thread de l'objet o2 a bien été modifiée...
    });

    qDebug() << "*** 9 -> Appel de fonction debugObjet() par timer (timeout=0)";
    QTimer::singleShot(0, o2, SLOT(debugObjet()));

    qDebug() << "*** 10 -> Appel de fonction debugObjetFiable()";
    o2->debugObjetFiable();

    o2->deleteLater();
}
