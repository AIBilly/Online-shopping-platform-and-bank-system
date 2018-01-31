#-------------------------------------------------
#
# Project created by QtCreator 2015-12-07T10:17:31
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = E-commerce
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    login.cpp \
    sign_up.cpp \
    cart.cpp \
    bind.cpp \
    pay.cpp

HEADERS  += mainwindow.h \
    login.h \
    sign_up.h \
    customer.h \
    product.h \
    cart.h \
    bind.h \
    pay.h

FORMS    += mainwindow.ui \
    login.ui \
    sign_up.ui \
    cart.ui \
    bind.ui \
    pay.ui
