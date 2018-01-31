#include "bind.h"
#include "ui_bind.h"

Bind::Bind(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Bind)
{
    ui->setupUi(this);

    udp_socket_tx = new QUdpSocket(this);
    udp_socket_rx = new QUdpSocket(this);

    int port_rx = 2002;

    Ip_Tx = QHostAddress("127.0.0.1");
    Port_Tx = 2001;
    udp_socket_rx->bind(QHostAddress::LocalHost, port_rx);

    connect(udp_socket_rx, SIGNAL(readyRead()),this, SLOT(rx_udp()));
}

Bind::~Bind()
{
    delete ui;
}

void Bind::on_confirm_clicked()
{
    if(ui->cardnumber->text()=="\0")
    {
        QMessageBox::warning(this, "Warning", "Please input the cardnumber!", QMessageBox::Yes | QMessageBox::No);
        clear();
    }
    else
    {
        if(ui->password->text()=="\0")
        {
            QMessageBox::warning(this, "Warning", "Please input the password!", QMessageBox::Yes | QMessageBox::No);
            clear();
        }
        else
        {
            int card_count = customer.getCardlistNumber(current_cus);
            int flag = 0;
            for(int e=0;e<card_count;e++)
            {
                if(ui->cardnumber->text()==customer.getCard(current_cus,e))
                {
                    flag = 1;
                }
            }
            if(flag==1)
            {
                QMessageBox::warning(this, "Warning", "The card is already binded!", QMessageBox::Yes | QMessageBox::No);
            }
            else
            {
                QByteArray datagram;
                QDataStream out(&datagram,QIODevice::WriteOnly);
                out << 1 <<ui->cardnumber->text()<<ui->password->text();
                udp_socket_tx->writeDatagram(datagram, datagram.size(), Ip_Tx, Port_Tx);
            }
        }
    }
}

void Bind::clear()
{
    ui->cardnumber->clear();
    ui->password->clear();
    ui->cardnumber->setFocus();
}

void Bind::closeEvent( QCloseEvent * event )
{
    event->accept();
    clear();
}

void Bind::rx_udp()
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
            QMessageBox::critical(this, "critical", "Wrong password!", QMessageBox::Yes | QMessageBox::No);
            break;
        case 0:
            QMessageBox::information(this, "information", "Succeeded.", QMessageBox::Yes | QMessageBox::No);
            customer.add_card_list(current_cus,ui->cardnumber->text());
            accept();
            break;
        default:
            break;
        }
    }
}
