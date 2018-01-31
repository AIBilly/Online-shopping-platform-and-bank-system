#ifndef CUSTOMER
#define CUSTOMER

#include "product.h"

using namespace std;

struct MyCart{
    QString category;
    QString name;
    int quantity;
};

struct cus{
    QString username;
    QString password;
    int cart_num;
    QVector<MyCart> cart;
    int card_num;
    QVector<QString> cardlist;
};

class Customer{
private:
    int cus_amount;
    QFile* file;
    QVector<cus> vec;

public:
    Customer()
    {
        cus_amount = 0;
        file=new QFile("customerlist.txt");
        if (!file->open(QIODevice::ReadOnly))
        {
            vec.clear();
        }
        else
        {
            QDataStream fin(file);
            while (!fin.atEnd())
            {
                cus temp;
                fin >> temp.username >> temp.password >> temp.cart_num;
                for (int e = 0; e < temp.cart_num; e++)
                {
                    MyCart temp1;
                    fin >> temp1.category >> temp1.name >> temp1.quantity;
                    temp.cart.push_back(temp1);
                }
                fin >> temp.card_num;
                for (int e = 0; e < temp.card_num; e++)
                {
                    QString card_n_t;
                    fin >> card_n_t;
                    temp.cardlist.push_back(card_n_t);
                }
                vec.push_back(temp);
                cus_amount++;
            }
            file->close();
        }
    }

    int add_cus(QString username,QString password)
    {
        cus temp;
        for (int i = 0; i < cus_amount; i++)
        {
            if(vec[i].username == username)
                return -1;
        }
        temp.username = username;
        temp.password = password;
        temp.cart_num = 0;
        temp.card_num = 0;
        vec.push_back(temp);
        cus_amount++;
        return 0;
    }

    void add_card_list(int subscript,QString cardnumber)
    {
        vec[subscript].cardlist.push_back(cardnumber);
        vec[subscript].card_num++;
    }

    int getCartNumber(int subscript)
    {
        return vec[subscript].cart_num;
    }

    MyCart getCartElement(int subscript1,int subscript2)
    {
        return vec[subscript1].cart[subscript2];
    }

    QString getCartElementCategory(int subscript1,int subscript2)
    {
        return vec[subscript1].cart[subscript2].category;
    }

    QString getCartElementName(int subscript1,int subscript2)
    {
        return vec[subscript1].cart[subscript2].name;
    }

    int getCartElementQuantity(int subscript1,int subscript2)
    {
        return vec[subscript1].cart[subscript2].quantity;
    }

    int getCardlistNumber(int subscript)
    {
        return vec[subscript].card_num;
    }

    void saveCart(int subscript,QString cate,QString name,int quan)
    {
        MyCart temp;
        temp.category = cate;
        temp.name = name;
        temp.quantity = quan;
        vec[subscript].cart.push_back(temp);
        vec[subscript].cart_num++;
    }

    void clearCart(int subscript)
    {
        vec[subscript].cart_num = 0;
        vec[subscript].cart.clear();
    }

    QString getCard(int subscript1,int subscript2)
    {
        return vec[subscript1].cardlist[subscript2];
    }

    QString getPasswordByUsername(QString username)
    {
        for (int i = 0; i < cus_amount; i++)
        {
            if(vec[i].username == username)
                return vec[i].password;
        }
        return NULL;
    }

    int getSubscript(QString username)
    {
        for (int i = 0; i < cus_amount; i++)
        {
            if(vec[i].username == username)
                return i;
        }
        return -1;
    }

    void save_information()
    {
        file->open(QIODevice::WriteOnly);
        QDataStream fout(file);
        file->resize(0);
        for (int i = 0; i < cus_amount; i++)
        {
            fout << vec[i].username << vec[i].password << vec[i].cart_num;
            for (int e = 0; e < vec[i].cart_num; e++)
            {
                fout << vec[i].cart[e].category << vec[i].cart[e].name << vec[i].cart[e].quantity;
            }
            fout << vec[i].card_num;
            for (int e = 0; e < vec[i].card_num; e++)
            {
                fout << vec[i].cardlist[e];
            }
        }
        file->close();
    }
};

#endif // CUSTOMER

