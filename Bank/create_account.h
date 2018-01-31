#ifndef CREATE_ACCOUNT_H
#define CREATE_ACCOUNT_H

#include <QDialog>
#include <QMessageBox>
#include <QtGui>
#include <QCloseEvent>
#include "bank.h"

extern Bank bank;

namespace Ui {
class Create_account;
}

class Create_account : public QDialog
{
    Q_OBJECT

public:
    explicit Create_account(QWidget *parent = 0);
    void closeEvent(QCloseEvent *event);
    void clear();
    ~Create_account();

private slots:
    void on_confirm_clicked();

private:
    Ui::Create_account *ui;
};

#endif // CREATE_ACCOUNT_H
