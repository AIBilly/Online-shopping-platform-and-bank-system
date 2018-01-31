#include "login.h"
#include "ui_login.h"

login::login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
    clear();
    ac_file=new QFile("activities.txt");
    if (!ac_file->open(QIODevice::ReadOnly))
    {
        ac_levels = 0;
    }
    else
    {
        QTextStream fin(ac_file);
        QString line;
        int rea,min;
        while (!fin.atEnd())
        {
            line = fin.readLine();
            QStringList myline = line.split(" ");
            rea = myline[0].toInt(0,10);
            min = myline[1].toInt(0,10);
            rh.push_back(rea);
            ms.push_back(min);
            ac_levels++;
        }
        ac_file->close();
    }
}

login::~login()
{
    delete ui;
}

void login::on_log_in_clicked()
{
    if(ui->username->text()=="\0")
    {
        QMessageBox::warning(this, "Warning", "Please input the username!", QMessageBox::Yes | QMessageBox::No);
        clear();
    }
    else
    {
        QString pwd = customer.getPasswordByUsername(ui->username->text());
        if(pwd==NULL)
        {
            QMessageBox::critical(this, "critical", "Cannot find the customer!", QMessageBox::Yes | QMessageBox::No);
            clear();
        }
        else
        {
            if(pwd!=ui->password->text())
            {
                QMessageBox::critical(this, "critical", "Wrong password!", QMessageBox::Yes | QMessageBox::No);
                clear();
            }
            else
            {
                current_cus = customer.getSubscript(ui->username->text());
                accept();
            }
        }
    }
}

void login::on_sign_up_clicked()
{
    sign_up_dlg.setAttribute(Qt::WA_ShowModal, true);
//    sign_up_dlg.setWindowModality(Qt::WindowModal);
    sign_up_dlg.exec();
}

void login::clear()
{
    ui->username->clear();
    ui->password->clear();
    ui->username->setFocus();
}

void login::closeEvent( QCloseEvent * event )
{
    event->accept();
    clear();
}
