#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include <QMessageBox>
#include <QCloseEvent>
#include <QTableWidget>
#include "cart.h"
#include "customer.h"
#include "bind.h"

extern Customer customer;
extern QVector<Product*> products;
extern QList<int> vec_cart;
extern int count_pro;
extern double dis_food;
extern double dis_clothes;
extern double dis_book;
extern int ac_levels;
extern QVector<int> rh;
extern QVector<int> ms;

static const int EXIT_CODE_REBOOT = -2;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void closeEvent(QCloseEvent *event);
    void initialize();
    void refresh();
    ~MainWindow();

private slots:
    void on_logout_clicked();

    void on_add_to_cart_clicked();

    void on_view_cart_clicked();

    void on_bind_card_clicked();

private:
    QFile* pro_info;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
