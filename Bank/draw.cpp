#include "draw.h"
#include "ui_draw.h"

Draw::Draw(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Draw)
{
    ui->setupUi(this);
}

Draw::~Draw()
{
    delete ui;
}

void Draw::on_confirm_clicked()
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
                        if(ui->amount->text()>bank.getInformation(6,subs))
                        {
                            QMessageBox::critical(this, "critical", "Balance insufficient!", QMessageBox::Yes | QMessageBox::No);
                            ui->amount->clear();
                            ui->amount->setFocus();
                        }
                        else
                        {
                            bank.update_information(2,subs,'\0',-amount);
                            QMessageBox::information(this, "information", "Drew successfully, your balance is: " + bank.getInformation(6,subs), QMessageBox::Yes | QMessageBox::No);
                            accept();
                            clear();
                        }
                    }
                }
            }
        }
    }
}

void Draw::clear()
{
    ui->card_number->clear();
    ui->pwd->clear();
    ui->amount->clear();
    ui->card_number->setFocus();
}

void Draw::closeEvent( QCloseEvent * event )
{
    event->accept();
    clear();
}
