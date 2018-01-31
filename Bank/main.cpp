#include "mainwindow.h"
#include "bank.h"
#include <QApplication>

Bank bank;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    a.exec();
    bank.save_information();
    return 0;
}
