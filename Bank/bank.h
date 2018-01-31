#ifndef BANK
#define BANK

#include <QFile>
#include <QVector>
#include <QDebug>
#include "user.h"

using namespace std;

class Bank{
private:
    int useramount;
    QFile* file;
    QVector<User> vec;
public:
    Bank()
    {
        useramount = 0;
        file=new QFile("userlist.txt");
        if (!file->open(QIODevice::ReadOnly))
        {
            vec.clear();
        }
        else
        {
            QDataStream fin(file);
            while (!fin.atEnd())
            {
                User temp;
                fin >> temp.name >> temp.idcardnumber >> temp.cardnumber >> temp.password >> temp.bankname >> temp.amount;
                vec.push_back(temp);
                useramount++;
            }
            file->close();
        }
    }

    QString add_user(QString name,QString idcardnumber,QString password,QString bankname)
    {
        User temp;
        temp.name = name;
        temp.idcardnumber = idcardnumber;
        temp.cardnumber = QString::number(useramount + 10000,10);
        temp.password = password;
        temp.bankname = bankname;
        temp.amount = 0;
        vec.push_back(temp);
        useramount++;
        return temp.cardnumber;
    }

    int getAccountByCardnumber(QString cardnumber)
    {
        for (int i = 0; i < useramount; i++)
        {
            if(vec[i].cardnumber == cardnumber)
                return i;
        }
        return -1;
    }

    QString getInformation(int option,int subscript)
    {
        switch(option)
        {
        case 1:
            return vec[subscript].name;
        case 2:
            return vec[subscript].idcardnumber;
        case 3:
            return vec[subscript].cardnumber;
        case 4:
            return vec[subscript].password;
        case 5:
            return vec[subscript].bankname;
        case 6:
            return QString::number(vec[subscript].amount,'f',2);
        default:
            return NULL;
            break;
        }
    }

    void update_information(int option,int subscript,QString new_pwd,double amount)
    {
        switch(option)
        {
        case 1:
            vec[subscript].password = new_pwd;
            break;
        case 2:
            vec[subscript].amount = vec[subscript].amount + amount;
            break;
        default:
            break;
        }
    }

    void save_information()
    {
        file->open(QIODevice::WriteOnly);
        QDataStream fout(file);
        file->resize(0);
        for (int i = 0; i < useramount; i++)
        {
            fout << vec[i].name << vec[i].idcardnumber << vec[i].cardnumber << vec[i].password << vec[i].bankname << vec[i].amount;
        }
        file->close();
    }
};

#endif // BANK

