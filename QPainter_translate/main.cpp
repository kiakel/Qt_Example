#include "mainWidget.h"
#include <QApplication>
#include <QHBoxLayout>
#include <QByteArray>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    mainWidget w;
    w.show();
    return a.exec();
}
