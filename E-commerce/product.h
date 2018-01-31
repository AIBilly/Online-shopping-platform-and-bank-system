#ifndef PRODUCT
#define PRODUCT

#include <QFile>
#include <QString>
#include <QVector>
#include <QDebug>

class Product{
protected:
    QString category;
    QString name;
    double price;
    QString remark;
    int inventory;
    int quantity;

public:
    virtual double getPrePrice() = 0;
    QString getCategory()
    {
        return category;
    }

    QString getName()
    {
        return name;
    }

    double getPrice()
    {
        return price;
    }

    QString getRemark()
    {
        return remark;
    }

    int getInventory()
    {
        return inventory;
    }

    int getQuantity()
    {
        return quantity;
    }

    int changeQuantity(int value)
    {
        if(quantity+value<0)
        {
            quantity=0;
        }
        else if(quantity+value>inventory)
        {
            return -1;
        }
        else
        {
            quantity=quantity+value;
        }
        return quantity;
    }

    int changeQuantityTo(int value)
    {
        if(value>=0)
        {
            quantity = value;
            return quantity;
        }
        else
            return -1;
    }

    int changeInventory(int value)
    {
        inventory = inventory+value;
        return inventory+value;
    }
};

class Food:public Product{
private:
    double discount;
public:
    Food(double D,QString C,QString N,double P,QString R,int I,int Q)
    {
        discount = D;
        category = C;
        name = N;
        price = P;
        remark = R;
        inventory = I;
        quantity = Q;
    }

    virtual double getPrePrice()
    {
        return price*discount;
    }

};

class Clothes:public Product{
private:
    double discount;
public:
    Clothes(double D,QString C,QString N,double P,QString R,int I,int Q)
    {
        discount = D;
        category = C;
        name = N;
        price = P;
        remark = R;
        inventory = I;
        quantity = Q;
    }

    virtual double getPrePrice()
    {
        return price*discount;
    }

};

class Book:public Product{
private:
    double discount;
public:
    Book(double D,QString C,QString N,double P,QString R,int I,int Q)
    {
        discount = D;
        category = C;
        name = N;
        price = P;
        remark = R;
        inventory = I;
        quantity = Q;
    }

    virtual double getPrePrice()
    {
        return price*discount;
    }

};

#endif // PRODUCT

