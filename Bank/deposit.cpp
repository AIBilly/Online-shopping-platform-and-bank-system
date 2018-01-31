#include "deposit.h"
#include "ui_deposit.h"

Deposit::Deposit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Deposit)
{
    ui->setupUi(this);
    clear();
}

Deposit::~Deposit()
{
    delete ui;
}

void Deposit::on_confirm_clicked()
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
            if(ui->pwd->text()!=bank.getInformation(4,subs))
            {
                QMessageBox::critical(this, "critical", "Wrong password!", QMessageBox::Yes | QMessageBox::No);
                ui->pwd->clear();
                ui->pwd->setFocus();
            }
            else
            {
                if(ui->amount->text()=="\0")
                {
                    QMessageBox::critical(this, "critical", "Please input the amount!", QMessageBox::Yes | QMessageBox::No);
                    ui->amount->setFocus();
                }
                else
                {
                    double amount = ui->amount->text().toDouble(0);
                    if(/*amount%100!=0 || */amount<0)
                    {
                        QMessageBox::critical(this, "critical", "The amount must be positive!", QMessageBox::Yes | QMessageBox::No);
                        ui->amount->clear();
                        ui->amount->setFocus();
                    }
                    else
                    {
                        bank.update_information(2,subs,'\0',amount);
                        QMessageBox::information(this, "information", "Deposited successfully, your balance is: " + bank.getInformation(6,subs), QMessageBox::Yes | QMessageBox::No);
                        accept();
                        clear();
                    }
                }
            }
        }
    }
}

void Deposit::clear()
{
    ui->card_number->clear();
    ui->pwd->clear();
    ui->amount->clear();
    ui->card_number->setFocus();
}

void Deposit::closeEvent( QCloseEvent * event )
{
    event->accept();
    clear();
}
