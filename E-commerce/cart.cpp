#include "cart.h"
#include "ui_cart.h"

QList<QPushButton*> ButtonList;

Cart::Cart(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Cart)
{
    ui->setupUi(this);

    ui->view_product->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->view_product->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->view_product->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->view_product->setColumnWidth(5,30);
    ui->view_product->setColumnWidth(6,30);

    signalMapper = new QSignalMapper(this);
    total = 0;
    count_b = 0;
    ButtonList.clear();
    QList<int> ::iterator current;
    for(current = vec_cart.begin();current!=vec_cart.end();current++)
    {
        double price = products[*current]->getPrePrice();
        int quantity = products[*current]->getQuantity();
        int rowIndex = ui->view_product->rowCount();
        ui->view_product->setRowCount(rowIndex + 1);
        ui->view_product->setItem(rowIndex,0,new QTableWidgetItem(products[*current]->getName()));
        ui->view_product->setItem(rowIndex,1,new QTableWidgetItem(products[*current]->getCategory()));
        ui->view_product->setItem(rowIndex,2,new QTableWidgetItem(QString::number(products[*current]->getPrice(),'f',2)));
        ui->view_product->setItem(rowIndex,3,new QTableWidgetItem(QString::number(price,'f',2)));
        ui->view_product->setItem(rowIndex,4,new QTableWidgetItem(QString::number(quantity,10)));

        Button = new QPushButton;
        Button->setText("+");
        Button->setMaximumWidth(30);
        ui->view_product->setCellWidget(rowIndex,5,Button);
        ButtonList.append(Button);
        connect(Button, SIGNAL(clicked()), signalMapper, SLOT(map()));
        signalMapper->setMapping(Button,count_b);
        count_b++;

        Button = new QPushButton;
        Button->setText("-");
        Button->setMaximumWidth(30);
        ui->view_product->setCellWidget(rowIndex,6,Button);
        ButtonList.append(Button);
        connect(Button, SIGNAL(clicked()), signalMapper, SLOT(map()));
        signalMapper->setMapping(Button,count_b);
        count_b++;

        total = total + (price * quantity);
    }
    ui->view_product->resizeColumnToContents(0);
    connect(signalMapper, SIGNAL(mapped(int)), this, SLOT(buttons_pressed(int)));
    ui->total->setText(QString::number(total,'f',2));
}

Cart::~Cart()
{
    delete ui;
}

void Cart::on_increase_clicked()
{
    QList<QTableWidgetSelectionRange> ranges=ui->view_product->selectedRanges();
    if(ranges.size()==0)
    {
        QMessageBox::warning(this, "Warning", "Please select the product!", QMessageBox::Yes | QMessageBox::No);
    }
    else
    {
        int value = ui->quantity->text().toInt(0,10);
        if(value != 0)
        {
            int row = ranges.at(0).topRow();
            int judge = products[*(vec_cart.begin()+row)]->changeQuantity(value);
            //qDebug()<<judge;
            if(judge == -1)
            {
                QMessageBox::warning(this, "Warning", "Insufficient inventory!", QMessageBox::Yes | QMessageBox::No);
            }
            else
            {
                refreshList();
            }
        }
    }
}

void Cart::on_decrease_clicked()
{
    QList<QTableWidgetSelectionRange> ranges=ui->view_product->selectedRanges();
    if(ranges.size()==0)
    {
        QMessageBox::warning(this, "Warning", "Please select the product!", QMessageBox::Yes | QMessageBox::No);
    }
    else
    {
        int value = ui->quantity->text().toInt(0,10);
        if(value != 0)
        {
            int row = ranges.at(0).topRow();
            int judge = products[*(vec_cart.begin()+row)]->changeQuantity(-value);
            if(judge == -1)
            {
                QMessageBox::warning(this, "Warning", "Insufficient inventory!", QMessageBox::Yes | QMessageBox::No);
            }
            else
            {
                refreshList();
            }
        }
    }
}

void Cart::on_del_clicked()
{
    QList<QTableWidgetSelectionRange> ranges=ui->view_product->selectedRanges();
    if(ranges.size()==0)
    {
        QMessageBox::warning(this, "Warning", "Please select the product!", QMessageBox::Yes | QMessageBox::No);
    }
    else
    {
        if(QMessageBox::question(this, "question", "Are you sure to delete?", QMessageBox::Yes | QMessageBox::No)==QMessageBox::Yes)
        {
            int row = ranges.at(0).topRow();
            int value = products[*(vec_cart.begin()+row)]->getQuantity();
            int judge = products[*(vec_cart.begin()+row)]->changeQuantity(-value);
            //qDebug()<<judge;
            if(judge == -1)
            {
                QMessageBox::warning(this, "Warning", "Delete error!", QMessageBox::Yes | QMessageBox::No);
            }
            else
            {
                refreshList();
            }
        }
    }
}

void Cart::on_go_to_pay_clicked()
{
    Pay paydlg;
    paydlg.exec();
    refreshList();
}

void Cart::buttons_pressed(int number)
{
    int value;
    if(number%2 == 0)
        value = 1;
    else
        value = -1;
    int row = number/2;
    int pre_q = products[*(vec_cart.begin()+row)]->getQuantity();
    int judge = products[*(vec_cart.begin()+row)]->changeQuantity(value);
    if(judge == -1)
    {
        QMessageBox::warning(this, "Warning", "Insufficient inventory!", QMessageBox::Yes | QMessageBox::No);
    }
    else
    {
        ui->view_product->setItem(row,4,new QTableWidgetItem(QString::number(judge,10)));
        total = total + (products[*(vec_cart.begin()+row)]->getPrePrice()*(judge - pre_q));
        ui->total->setText(QString::number(total,'f',2));
    }
    //qDebug()<<number;
}

void Cart::refreshList()
{
    disconnect(signalMapper, SIGNAL(mapped(int)), this, SLOT(buttons_pressed(int)));
    delete signalMapper;
    ui->view_product->setRowCount(0);
    ui->view_product->clearContents();
    signalMapper = new QSignalMapper(this);
    total = 0;
    count_b = 0;
    ButtonList.clear();
    //qDebug()<<1;
    QList<int> ::iterator current;
    for(current = vec_cart.begin();current!=vec_cart.end();current++)
    {
        int rowIndex = ui->view_product->rowCount();
        //qDebug()<<products[*current]->getQuantity();
        if(products[*current]->getQuantity()==0)
        {
            vec_cart.erase(current);
        }
        else
        {
            double price = products[*current]->getPrePrice();
            int quantity = products[*current]->getQuantity();
            ui->view_product->setRowCount(rowIndex + 1);
            ui->view_product->setItem(rowIndex,0,new QTableWidgetItem(products[*current]->getName()));
            ui->view_product->setItem(rowIndex,1,new QTableWidgetItem(products[*current]->getCategory()));
            ui->view_product->setItem(rowIndex,2,new QTableWidgetItem(QString::number(products[*current]->getPrice(),'f',2)));
            ui->view_product->setItem(rowIndex,3,new QTableWidgetItem(QString::number(products[*current]->getPrePrice(),'f',2)));
            ui->view_product->setItem(rowIndex,4,new QTableWidgetItem(QString::number(products[*current]->getQuantity(),10)));
            //qDebug()<<1;
            Button = new QPushButton;
            Button->setText("+");
            Button->setMaximumWidth(30);
            ui->view_product->setCellWidget(rowIndex,5,Button);
            ButtonList.append(Button);
            connect(Button, SIGNAL(clicked()), signalMapper, SLOT(map()));
            signalMapper->setMapping(Button,count_b);
            count_b++;
            //qDebug()<<1;
            Button = new QPushButton;
            Button->setText("-");
            Button->setMaximumWidth(30);
            ui->view_product->setCellWidget(rowIndex,6,Button);
            ButtonList.append(Button);
            connect(Button, SIGNAL(clicked()), signalMapper, SLOT(map()));
            signalMapper->setMapping(Button,count_b);
            count_b++;
            total = total + (price * quantity);
        }
    }
    ui->view_product->resizeColumnToContents(0);
    connect(signalMapper, SIGNAL(mapped(int)), this, SLOT(buttons_pressed(int)));
    ui->total->setText(QString::number(total,'f',2));
}

void Cart::closeEvent( QCloseEvent * event )
{
    event->accept();
    refreshList();
}
