#include "pay.h"
#include "ui_pay.h"

Pay::Pay(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Pay)
{
    ui->setupUi(this);

    int level = -1;
    for(int i=ac_levels-1;i>=0;i--)
    {
        if(total>=rh[i])
        {
            level = i;
            break;
        }
    }
    if(level!=-1)
    {
        ac_total = total - ms[level];
        ui->total->setText(QString::number(ac_total,'f',2)+"(reach "+QString::number(rh[level],10)+" and get "+QString::number(ms[level],10)+" reduce)");
    }
    else
    {
        ac_total = total;
        ui->total->setText(QString::number(ac_total,'f',2));
    }
    ui->cardlist->setEditable(false);
    int card_count = customer.getCardlistNumber(current_cus);
    for(int e=0;e<card_count;e++)
    {
        ui->cardlist->addItem(customer.getCard(current_cus,e));
    }

    udp_socket_tx = new QUdpSocket(this);
    udp_socket_rx = new QUdpSocket(this);

    int port_rx = 2002;

    Ip_Tx = QHostAddress("127.0.0.1");
    Port_Tx = 2001;
    udp_socket_rx->bind(QHostAddress::LocalHost, port_rx);

    connect(udp_socket_rx, SIGNAL(readyRead()),this, SLOT(rx_udp()));
}

Pay::~Pay()
{
    delete ui;
}

void Pay::closeEvent( QCloseEvent * event )
{
    event->accept();
}

void Pay::rx_udp()
{
    while (udp_socket_rx->hasPendingDatagrams())
    {
        int c;
        QByteArray datagram;
        datagram.resize(udp_socket_rx->pendingDatagramSize());

        QHostAddress sender;
        quint16 senderPort;

        udp_socket_rx->readDatagram(datagram.data(), datagram.size(),&sender, &senderPort);

        QDataStream in(&datagram, QIODevice::ReadOnly);
        in>>c;
        switch(c)
        {
        case -2:
            QMessageBox::critical(this, "critical", "Cannot find the account!", QMessageBox::Yes | QMessageBox::No);
            break;
        case -1:
            QMessageBox::critical(this, "critical", "Insufficient balance!", QMessageBox::Yes | QMessageBox::No);
            break;
        case 0:
            QMessageBox::information(this, "information", "Succeeded.", QMessageBox::Yes | QMessageBox::No);
            clearCart();
            accept();
            break;
        default:
            break;
        }
    }
}

void Pay::on_confirm_clicked()
{
    if(ui->cardlist->count()==0)
    {
        QMessageBox::warning(this, "Warning", "Please bind a card first!", QMessageBox::Yes | QMessageBox::No);
    }
    else
    {
        QByteArray datagram;
        QDataStream out(&datagram,QIODevice::WriteOnly);
        out << 2 <<ac_total<<ui->cardlist->currentText();
        udp_socket_tx->writeDatagram(datagram, datagram.size(), Ip_Tx, Port_Tx);
    }
}

void Pay::clearCart()
{
    QList<int> ::iterator current;
    for(current = vec_cart.begin();current!=vec_cart.end();current++)
    {
        int value = products[*current]->getQuantity();
        int del_inven = products[*current]->changeInventory(-value);
        int del_quan = products[*current]->changeQuantity(-value);
        del_inven = del_quan = 0;
    }
    vec_cart.clear();
    customer.clearCart(current_cus);

    pro_info=new QFile("productInfo.txt");
    pro_info->open(QIODevice::Text|QIODevice::WriteOnly);
    QTextStream fout(pro_info);
    fout << dis_food << " " << dis_clothes << " " << dis_book << "\n";
    for(int i=0;i<count_pro;i++)
    {
        if(products[i]->getCategory()=="food")
        {
            fout << 1 << " ";
        }
        else if(products[i]->getCategory()=="clothes")
        {
            fout << 2 << " ";
        }
        else if(products[i]->getCategory()=="book")
        {
            fout << 3 << " ";
        }
        QString pro_name = products[i]->getName();
        double price = products[i]->getPrice();
        QString remark = products[i]->getRemark();
        int inventory = products[i]->getInventory();
        fout << pro_name << " " << price << " " << remark << " " << inventory << "\n";
    }
    pro_info->close();
}
