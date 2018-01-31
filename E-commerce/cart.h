#ifndef CART_H
#define CART_H

#include <QDialog>
#include <QtGui>
#include <QList>
#include <QMessageBox>
#include <QCloseEvent>
#include <QTableWidget>
#include <QSignalMapper>
#include "customer.h"
#include "pay.h"

extern Customer customer;
extern QVector<Product*> products;
extern QList<int> vec_cart;
extern double total;
extern int count_pro;
extern double dis_food;
extern double dis_clothes;
extern double dis_book;

namespace Ui {
class Cart;
}

class Cart : public QDialog
{
    Q_OBJECT

public:
    explicit Cart(QWidget *parent = 0);
    void closeEvent(QCloseEvent *event);
    void refreshList();
    ~Cart();

private slots:
    void on_increase_clicked();

    void on_decrease_clicked();

    void on_del_clicked();

    void on_go_to_pay_clicked();

    void buttons_pressed(int number);

private:
    Ui::Cart *ui;
    QPushButton* Button;
    QSignalMapper *signalMapper;
    int count_b;
};

#endif // CART_H
