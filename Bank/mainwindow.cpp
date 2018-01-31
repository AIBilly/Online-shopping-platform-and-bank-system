#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    udp_socket_tx = new QUdpSocket(this);
    udp_socket_rx = new QUdpSocket(this);

    int port_rx = 2001;

    Ip_Tx = QHostAddress("127.0.0.1");
    Port_Tx = 2002;
    udp_socket_rx->bind(QHostAddress::LocalHost, port_rx);

    connect(udp_socket_rx, SIGNAL(readyRead()),this, SLOT(wait_for_socket()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_create_account_clicked()
{
    CA.setAttribute(Qt::WA_ShowModal, true);
    CA.exec();
}

void MainWindow::on_change_password_clicked()
{
    CP.setAttribute(Qt::WA_ShowModal, true);
    CP.exec();
}

void MainWindow::on_deposit_clicked()
{
    DE.setAttribute(Qt::WA_ShowModal, true);
    DE.exec();
}

void MainWindow::on_draw_clicked()
{
    DA.setAttribute(Qt::WA_ShowModal, true);
    DA.exec();
}

void MainWindow::closeEvent( QCloseEvent * event )
{
    switch( QMessageBox::information( this, tr("exit"),tr("Do you really want to exit?"),tr("Yes"), tr("No"),0, 1 ) )
    {
    case 0:
       event->accept();
       break;
    case 1:
    default:
       event->ignore();
       break;
    }
}

void MainWindow::wait_for_socket()
{
    while (udp_socket_rx->hasPendingDatagrams())
    {
        int operation;
        double total;
        QString card_number,password;
        QByteArray datagram;
        datagram.resize(udp_socket_rx->pendingDatagramSize());

        QHostAddress sender;
        quint16 senderPort;

        udp_socket_rx->readDatagram(datagram.data(), datagram.size(),&sender, &senderPort);

        QDataStream in(&datagram, QIODevice::ReadOnly);
        in>>operation;
        switch(operation)
        {
            case 1:
            {
                in >> card_number >> password;
                int subs = bank.getAccountByCardnumber(card_number);
                if(subs==-1)
                {
                    QByteArray datagram;
                    QDataStream out(&datagram,QIODevice::WriteOnly);
                    out << -2;
                    udp_socket_tx->writeDatagram(datagram, datagram.size(), Ip_Tx, Port_Tx);
                }
                else if(password!=bank.getInformation(4,subs))
                {
                    QByteArray datagram;
                    QDataStream out(&datagram,QIODevice::WriteOnly);
                    out << -1;
                    udp_socket_tx->writeDatagram(datagram, datagram.size(), Ip_Tx, Port_Tx);
                }
                else
                {
                    QByteArray datagram;
                    QDataStream out(&datagram,QIODevice::WriteOnly);
                    out << 0;
                    udp_socket_tx->writeDatagram(datagram, datagram.size(), Ip_Tx, Port_Tx);
                }
                break;
            }
            case 2:
            {
                in >> total >> card_number;
                int subs = bank.getAccountByCardnumber(card_number);
                if(subs==-1)
                {
                    QByteArray datagram;
                    QDataStream out(&datagram,QIODevice::WriteOnly);
                    out << -2;
                    udp_socket_tx->writeDatagram(datagram, datagram.size(), Ip_Tx, Port_Tx);
                }
                else if(total>bank.getInformation(6,subs).toDouble(0))
                {
                    QByteArray datagram;
                    QDataStream out(&datagram,QIODevice::WriteOnly);
                    out << -1;
                    udp_socket_tx->writeDatagram(datagram, datagram.size(), Ip_Tx, Port_Tx);
                }
                else
                {
                    bank.update_information(2,subs,'\0',-total);
                    QByteArray datagram;
                    QDataStream out(&datagram,QIODevice::WriteOnly);
                    out << 0;
                    udp_socket_tx->writeDatagram(datagram, datagram.size(), Ip_Tx, Port_Tx);
                }
                break;
            }
            default:
            {
                break;
            }
        }
    }
}
