#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include <QtGui>
#include <QMessageBox>
#include <QCloseEvent>
#include "customer.h"
#include "sign_up.h"

extern Customer customer;
extern int ac_levels;
extern QVector<int> rh;
extern QVector<int> ms;
extern int current_cus;

namespace Ui {
class login;
}

class login : public QDialog
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = 0);
    void closeEvent(QCloseEvent *event);
    void clear();
    ~login();

private slots:
    void on_log_in_clicked();

    void on_sign_up_clicked();

private:
    Ui::login *ui;
    QFile* ac_file;
    sign_up sign_up_dlg;
};

#endif // LOGIN_H
