#ifndef DRAW_H
#define DRAW_H

#include <QDialog>
#include <QMessageBox>
#include <QtGui>
#include <QCloseEvent>
#include "bank.h"

extern Bank bank;

namespace Ui {
class Draw;
}

class Draw : public QDialog
{
    Q_OBJECT

public:
    explicit Draw(QWidget *parent = 0);
    void closeEvent(QCloseEvent *event);
    void clear();
    ~Draw();

private slots:
    void on_confirm_clicked();

private:
    Ui::Draw *ui;
};

#endif // DRAW_H
