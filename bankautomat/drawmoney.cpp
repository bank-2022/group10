#include "drawmoney.h"
#include "ui_drawmoney.h"

DrawMoney::DrawMoney(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DrawMoney)
{
    ui->setupUi(this);
}

DrawMoney::~DrawMoney()
{
    delete ui;
}

void DrawMoney::on_btnDraw20_clicked()
{

}


void DrawMoney::on_btnDraw40_clicked()
{

}


void DrawMoney::on_btnDraw60_clicked()
{

}


void DrawMoney::on_btnDraw100_clicked()
{

}


void DrawMoney::on_btnDraw200_clicked()
{

}


void DrawMoney::on_btnDraw500_clicked()
{

}


void DrawMoney::on_btnDrawClose_clicked()
{
    this->close();

}

