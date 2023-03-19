#include <QCoreApplication>
#include <QDebug>
#include "Controller.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    qDebug() << "Adresse de a : " << &a;
    qDebug() << "   ID du thread de l'application : " << a.thread()->currentThreadId();
    qDebug() << "";

    Controller ctrl;
    ctrl.start();    

    return a.exec();
}
