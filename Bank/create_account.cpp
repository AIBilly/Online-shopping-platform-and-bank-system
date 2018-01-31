#include "create_account.h"
#include "ui_create_account.h"

Create_account::Create_account(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Create_account)
{
    ui->setupUi(this);
    clear();
}

Create_account::~Create_account()
{
    delete ui;
}

void Create_account::on_confirm_clicked()
{
    if(ui->name->text()=="\0")
    {
        QMessageBox::critical(this, "critical", "Please input the name!", QMessageBox::Yes | QMessageBox::No);
        ui->name->setFocus();
    }
    else
    {
        if(ui->idcard_number->text()=="\0")
        {
            QMessageBox::critical(this, "critical", "Please input the IDcard number!", QMessageBox::Yes | QMessageBox::No);
            ui->idcard_number->setFocus();
        }
        else
        {
            if(ui->pwd_1->text()=="\0")
            {
               QMessageBox::critical(this, "critical", "Please input the password!", QMessageBox::Yes | QMessageBox::No);
               ui->pwd_1->setFocus();
            }
            else
            {
                if(ui->pwd_2->text()=="\0")
                {
                    QMessageBox::critical(this, "critical", "Please input the password again!", QMessageBox::Yes | QMessageBox::No);
                    ui->pwd_2->setFocus();
                }
                else
                {
                    if(ui->pwd_1->text()!=ui->pwd_2->text())
                    {
                        QMessageBox::critical(this, "critical", "The two passwords you have input is not the same,please input again!!", QMessageBox::Yes | QMessageBox::No);
                        ui->pwd_1->clear();
                        ui->pwd_2->clear();
                        ui->pwd_1->setFocus();
                    }
                    else
                    {
                        QString cardnumber;
                        if(ui->BOC->isChecked())
                            cardnumber = bank.add_user(ui->name->text(),ui->idcard_number->text(),ui->pwd_1->text(),"BOC");
                        if(ui->ICBC->isChecked())
                            cardnumber = bank.add_user(ui->name->text(),ui->idcard_number->text(),ui->pwd_1->text(),"ICBC");
                        if(ui->CCB->isChecked())
                            cardnumber = bank.add_user(ui->name->text(),ui->idcard_number->text(),ui->pwd_1->text(),"CCB");
                        if(ui->BOCOM->isChecked())
                            cardnumber = bank.add_user(ui->name->text(),ui->idcard_number->text(),ui->pwd_1->text(),"BOCOM");
                        QMessageBox::information(this, "information", "Account created successfully, your card number is: " + cardnumber, QMessageBox::Yes | QMessageBox::No);
                        accept();
                        clear();
                    }
                }
            }
        }
    }
}

void Create_account::clear()
{
    ui->name->clear();
    ui->idcard_number->clear();
    ui->pwd_1->clear();
    ui->pwd_2->clear();
    ui->BOC->setChecked(true);
    ui->name->setFocus();
}

void Create_account::closeEvent( QCloseEvent * event )
{
    event->accept();
    clear();
}
