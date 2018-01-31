#ifndef PAY_H
#define PAY_H

#include <QDialog>
#include <QtGui>
#include <QList>
#include <QMessageBox>
#include <QCloseEvent>
#include <QtNetwork/QUdpSocket>
#include "customer.h"

extern Customer customer;
extern QVector<Product*> products;
extern QList<int> vec_cart;
extern int current_cus;
extern int ac_levels;
extern QVector<int> rh;
extern QVector<int> ms;
extern double total;
extern int count_pro;
extern double dis_food;
extern double dis_clothes;
extern double dis_book;

namespace Ui {
class Pay;
}

class Pay : public QDialog
{
    Q_OBJECT

public:
    explicit Pay(QWidget *parent = 0);
    void closeEvent(QCloseEvent *event);
    void clearCart();
    ~Pay();

private slots:
    void rx_udp();

    void on_confirm_clicked();

private:
    Ui::Pay *ui;
    double ac_total;
    QFile* pro_info;

    QUdpSocket *udp_socket_tx;
    QUdpSocket *udp_socket_rx;

    QHostAddress Ip_Tx;
    int Port_Tx;
};

#endif // PAY_H
