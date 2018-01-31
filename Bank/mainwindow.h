#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCloseEvent>
#include <QtNetwork/QUdpSocket>
#include "create_account.h"
#include "change_password.h"
#include "deposit.h"
#include "draw.h"
#include "bank.h"

extern Bank bank;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void closeEvent(QCloseEvent *event);
    ~MainWindow();

private slots:
    void on_create_account_clicked();

    void on_change_password_clicked();

    void on_deposit_clicked();

    void on_draw_clicked();

    void wait_for_socket();

private:
    Ui::MainWindow *ui;
    Create_account CA;
    Change_password CP;
    Deposit DE;
    Draw DA;
    QUdpSocket *udp_socket_tx;
    QUdpSocket *udp_socket_rx;

    QHostAddress Ip_Tx;
    int Port_Tx;
};

#endif // MAINWINDOW_H
