#include "mainwindow.h"
#include "customer.h"
#include "login.h"
#include <QApplication>

Customer customer;
QVector<Product*> products;
int ac_levels = 0;
QVector<int> rh;
QVector<int> ms;
QList<int> vec_cart;
double total= 0;
int current_cus = -1;
int count_pro = 0;
double dis_food = 1;
double dis_clothes = 1;
double dis_book = 1;

int main(int argc, char *argv[])
{
    int currentExitCode = 0;
    QApplication a(argc, argv);
    do
    {
        login logindlg;
        if(logindlg.exec()==QDialog::Accepted)
        {
            MainWindow w;
            w.show();
            currentExitCode = a.exec();
        }
        else return 0;
        customer.save_information();
    }while(currentExitCode == EXIT_CODE_REBOOT);
    return 0;
}
