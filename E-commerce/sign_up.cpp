#include "sign_up.h"
#include "ui_sign_up.h"

sign_up::sign_up(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::sign_up)
{
    ui->setupUi(this);
    clear();
}

sign_up::~sign_up()
{
    delete ui;
}

void sign_up::on_ok_clicked()
{
    if(ui->username->text()=="\0")
    {
        QMessageBox::critical(this, "critical", "Please input the username!", QMessageBox::Yes | QMessageBox::No);
        ui->username->setFocus();
    }
    else
    {
        if(ui->password1->text()=="\0")
        {
           QMessageBox::critical(this, "critical", "Please input the password!", QMessageBox::Yes | QMessageBox::No);
           ui->password1->setFocus();
        }
        else
        {
            if(ui->password2->text()=="\0")
            {
                QMessageBox::critical(this, "critical", "Please input the password again!", QMessageBox::Yes | QMessageBox::No);
                ui->password2->setFocus();
            }
            else
            {
                if(ui->password1->text()!=ui->password2->text())
                {
                    QMessageBox::critical(this, "critical", "The two passwords you have input is not the same,please input again!!", QMessageBox::Yes | QMessageBox::No);
                    clear();
                }
                else
                {
                    if(customer.add_cus(ui->username->text(),ui->password1->text())!=0)
                    {
                        QMessageBox::critical(this, "critical", "The username is already been used!!", QMessageBox::Yes | QMessageBox::No);
                        clear();
                    }
                    else
                    {
                        QMessageBox::information(this, "information", "Succeeded.", QMessageBox::Yes | QMessageBox::No);
                        accept();
                    }

                }
            }
        }
    }
}

void sign_up::clear()
{
    ui->username->clear();
    ui->password1->clear();
    ui->password2->clear();
    ui->username->setFocus();
}

void sign_up::closeEvent( QCloseEvent * event )
{
    event->accept();
    clear();
}
