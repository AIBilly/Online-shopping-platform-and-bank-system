#ifndef CHANGE_PASSWORD_H
#define CHANGE_PASSWORD_H

#include <QDialog>
#include <QMessageBox>
#include <QtGui>
#include <QCloseEvent>
#include "bank.h"

extern Bank bank;

namespace Ui {
class Change_password;
}

class Change_password : public QDialog
{
    Q_OBJECT

public:
    explicit Change_password(QWidget *parent = 0);
    void closeEvent(QCloseEvent *event);
    void clear();
    ~Change_password();

private slots:

    void on_comfirm_clicked();

private:
    Ui::Change_password *ui;
};

#endif // CHANGE_PASSWORD_H
