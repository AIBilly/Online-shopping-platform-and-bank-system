#ifndef DEPOSIT_H
#define DEPOSIT_H

#include <QDialog>
#include <QMessageBox>
#include <QtGui>
#include <QCloseEvent>
#include "bank.h"

extern Bank bank;

namespace Ui {
class Deposit;
}

class Deposit : public QDialog
{
    Q_OBJECT

public:
    explicit Deposit(QWidget *parent = 0);
    void closeEvent(QCloseEvent *event);
    void clear();
    ~Deposit();

private slots:
    void on_confirm_clicked();

private:
    Ui::Deposit *ui;
};

#endif // DEPOSIT_H
