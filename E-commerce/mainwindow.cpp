#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->activity->clear();
    QString text;
    for(int i=0;i<ac_levels;i++)
    {
        QString temp;
        temp = QString::number(rh[i],10)+"-"+QString::number(ms[i],10)+" ";
        text = text+temp;
    }
    ui->activity->setText(text);

    initialize();
    int re_cartnumber = customer.getCartNumber(current_cus);
    for(int i=0;i<re_cartnumber;i++)
    {
        MyCart re_element = customer.getCartElement(current_cus,i);
        for(int e = 0;e<count_pro;e++)
        {
            if(re_element.category==products[e]->getCategory() && re_element.name==products[e]->getName())
            {
                products[e]->changeQuantityTo(re_element.quantity);
            }
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_logout_clicked()
{
    if(vec_cart.size()!=0)
    {
        QList<int> ::iterator current;
        for(current = vec_cart.begin();current!=vec_cart.end();current++)
        {
            customer.saveCart(current_cus,products[*current]->getCategory(),products[*current]->getName(),products[*current]->getQuantity());
        }
    }
    current_cus = -1;
    qApp->exit( EXIT_CODE_REBOOT );
}

void MainWindow::on_add_to_cart_clicked()
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
            int judge = products[row]->changeQuantity(value);
            if(judge == -1)
            {
                QMessageBox::warning(this, "Warning", "Insufficient inventory!", QMessageBox::Yes | QMessageBox::No);
            }
            else
            {
                QMessageBox::information(this, "Info", "Added "+QString::number(value,10)+" "+products[row]->getName()+" to the cart, now you have "+QString::number(judge,10)+" in the cart.", QMessageBox::Yes | QMessageBox::No);
            }
        }
    }

}

void MainWindow::on_view_cart_clicked()
{
    for(int i=0;i<count_pro;i++)
    {
        if(products[i]->getQuantity()!=0)
        {
            QList<int> ::iterator current;
            int flag = 0;
            for(current = vec_cart.begin();current!=vec_cart.end();current++)
            {
                if(i == (*current))
                    flag = 1;
            }
            if(flag == 0)
            {
                vec_cart.push_back(i);
            }
        }
    }
    Cart mycart;
    mycart.exec();
    refresh();
}

void MainWindow::on_bind_card_clicked()
{
    Bind bind_dlg;
    bind_dlg.exec();
}

void MainWindow::closeEvent( QCloseEvent * event )
{
    switch( QMessageBox::information( this, tr("exit"),tr("Do you really want to exit?"),tr("Yes"), tr("No"),0, 1 ) )
    {
    case 0:
        if(vec_cart.size()!=0)
        {
            QList<int> ::iterator current;
            for(current = vec_cart.begin();current!=vec_cart.end();current++)
            {
                customer.saveCart(current_cus,products[*current]->getCategory(),products[*current]->getName(),products[*current]->getQuantity());
            }
        }
        event->accept();
        break;
    case 1:
    default:
        event->ignore();
        break;
    }
}

void MainWindow::initialize()
{
    products.clear();
    count_pro = 0;
    ui->view_product->clear();
    ui->view_product->setRowCount(0);
    QStringList header;
    header<<"Name :"<<"Category :"<<"Original price :"<<"Current price :"<<"Remark :"<<"Inventory :";
    ui->view_product->setHorizontalHeaderLabels(header);

    pro_info=new QFile("productInfo.txt");
    if (!pro_info->open(QIODevice::ReadOnly))
    {
        products.clear();
        QMessageBox::warning(this, "Warning", "Cannot find the product file!", QMessageBox::Yes | QMessageBox::No);
    }
    else
    {
        QTextStream fin(pro_info);
        QString line;
        line = fin.readLine();
        QStringList myline = line.split(" ");
        dis_food = myline[0].toDouble(0);
        dis_clothes = myline[1].toDouble(0);
        dis_book = myline[2].toDouble(0);
        while (!fin.atEnd())
        {
            line = fin.readLine();
            QStringList myline1 = line.split(" ");
            QString C = myline1[0],N = myline1[1],R = myline1[3];
            double P = myline1[2].toDouble(0);
            int I = myline1[4].toInt(0,10);
            switch(C.toInt(0,10))
            {
            case 1:
            {
                Food *f = new Food(dis_food,"food",N,P,R,I,0);
                products.push_back(f);
                count_pro++;
                break;
            }
            case 2:
            {
                Clothes *c = new Clothes(dis_clothes,"clothes",N,P,R,I,0);
                products.push_back(c);
                count_pro++;
                break;
            }
            case 3:
            {
                Book *b = new Book(dis_book,"book",N,P,R,I,0);
                products.push_back(b);
                count_pro++;
                break;
            }
            default:
                break;
            }
        }
        pro_info->close();
    }

    ui->view_product->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->view_product->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->view_product->setSelectionMode(QAbstractItemView::SingleSelection);

    for(int i=0;i<count_pro;i++)
    {
        int rowIndex = ui->view_product->rowCount();
        ui->view_product->setRowCount(rowIndex + 1);
        ui->view_product->setItem(rowIndex,0,new QTableWidgetItem(products[i]->getName()));
        ui->view_product->setItem(rowIndex,1,new QTableWidgetItem(products[i]->getCategory()));
        ui->view_product->setItem(rowIndex,2,new QTableWidgetItem(QString::number(products[i]->getPrice(),'f',2)));
        ui->view_product->setItem(rowIndex,3,new QTableWidgetItem(QString::number(products[i]->getPrePrice(),'f',2)));
        ui->view_product->setItem(rowIndex,4,new QTableWidgetItem(products[i]->getRemark()));
        ui->view_product->setItem(rowIndex,5,new QTableWidgetItem(QString::number(products[i]->getInventory(),10)));
    }
    ui->view_product->resizeColumnToContents(0);
}

void MainWindow::refresh()
{
    pro_info=new QFile("productInfo.txt");
    if (!pro_info->open(QIODevice::ReadOnly))
    {
        products.clear();
        QMessageBox::warning(this, "Warning", "Cannot find the product file!", QMessageBox::Yes | QMessageBox::No);
    }
    else
    {
        QTextStream fin(pro_info);
        QString line;
        line = fin.readLine();
        QStringList myline = line.split(" ");
        dis_food = myline[0].toDouble(0);
        dis_clothes = myline[1].toDouble(0);
        dis_book = myline[2].toDouble(0);
        int row = 0;
        while (!fin.atEnd())
        {
            line = fin.readLine();
            QStringList myline1 = line.split(" ");
            ui->view_product->setItem(row,5,new QTableWidgetItem(myline1[4]));
            row++;
        }
        pro_info->close();
    }
}
