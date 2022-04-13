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
