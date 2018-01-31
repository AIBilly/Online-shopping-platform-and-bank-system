#include "change_password.h"
#include "ui_change_password.h"

Change_password::Change_password(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Change_password)
{
    ui->setupUi(this);
    clear();
}

Change_password::~Change_password()
{
    delete ui;
}

void Change_password::on_comfirm_clicked()
{
    if(ui->card_number->text()=="\0")
    {
        QMessageBox::critical(this, "critical", "Please input the card number!", QMessageBox::Yes | QMessageBox::No);
        ui->card_number->setFocus();
    }
    else
    {
        int subs = bank.getAccountByCardnumber(ui->card_number->text());
        if(subs==-1)
        {
            QMessageBox::critical(this, "critical", "Cannot find the account!", QMessageBox::Yes | QMessageBox::No);
            ui->card_number->clear();
            ui->card_number->setFocus();
        }
        else
        {
            if(ui->idcard_number->text()!=bank.getInformation(2,subs))
            {
                QMessageBox::critical(this, "critical", "Wrong IDcard number!", QMessageBox::Yes | QMessageBox::No);
                ui->idcard_number->clear();
                ui->idcard_number->setFocus();
            }
            else
            {
                if(ui->ori_pwd->text()!=bank.getInformation(4,subs))
                {
                    QMessageBox::critical(this, "critical", "Wrong password!", QMessageBox::Yes | QMessageBox::No);
                    ui->ori_pwd->clear();
                    ui->ori_pwd->setFocus();
                }
                else
                {
                    if(ui->new_pwd_1->text()=="\0")
                    {
                       QMessageBox::critical(this, "critical", "Please input the new password!", QMessageBox::Yes | QMessageBox::No);
                       ui->new_pwd_1->setFocus();
                    }
                    else
                    {
                        if(ui->new_pwd_2->text()=="\0")
                        {
                            QMessageBox::critical(this, "critical", "Please input the new password again!", QMessageBox::Yes | QMessageBox::No);
                            ui->new_pwd_2->setFocus();
                        }
                        else
                        {
                            if(ui->new_pwd_1->text()!=ui->new_pwd_2->text())
                            {
                                QMessageBox::critical(this, "critical", "The two passwords you have input is not the same,please input again!!", QMessageBox::Yes | QMessageBox::No);
                                ui->new_pwd_1->clear();
                                ui->new_pwd_2->clear();
                                ui->new_pwd_1->setFocus();
                            }
                            else
                            {
                                bank.update_information(1,subs,ui->new_pwd_1->text(),0);
                                QMessageBox::information(this, "information", "Password updated successfully, your new password is: " + ui->new_pwd_1->text(), QMessageBox::Yes | QMessageBox::No);
                                accept();
                                clear();
                            }
                        }
                    }
                }
            }
        }
    }
}

void Change_password::clear()
{
    ui->card_number->clear();
    ui->idcard_number->clear();
    ui->ori_pwd->clear();
    ui->new_pwd_1->clear();
    ui->new_pwd_2->clear();
    ui->card_number->setFocus();
}

void Change_password::closeEvent( QCloseEvent * event )
{
    event->accept();
    clear();
}

