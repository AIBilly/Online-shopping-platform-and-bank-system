#ifndef BIND_H
#define BIND_H

#include <QDialog>
#include <QtGui>
#include <QList>
#include <QMessageBox>
#include <QCloseEvent>
#include <QtNetwork/QUdpSocket>
#include "customer.h"

extern Customer customer;
extern int current_cus;

namespace Ui {
class Bind;
}

class Bind : public QDialog
{
    Q_OBJECT

public:
    explicit Bind(QWidget *parent = 0);
    void closeEvent(QCloseEvent *event);
    void clear();
    ~Bind();

private slots:
    void on_confirm_clicked();
    void rx_udp();

private:
    Ui::Bind *ui;

    QUdpSocket *udp_socket_tx;
    QUdpSocket *udp_socket_rx;

    QHostAddress Ip_Tx;
    int Port_Tx;
};

#endif // BIND_H
