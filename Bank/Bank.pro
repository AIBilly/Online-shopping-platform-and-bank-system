#-------------------------------------------------
#
# Project created by QtCreator 2015-12-05T20:41:49
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Bank
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    create_account.cpp \
    change_password.cpp \
    deposit.cpp \
    draw.cpp

HEADERS  += mainwindow.h \
    create_account.h \
    change_password.h \
    deposit.h \
    draw.h \
    user.h \
    bank.h

FORMS    += mainwindow.ui \
    create_account.ui \
    change_password.ui \
    deposit.ui \
    draw.ui
