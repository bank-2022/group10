#include "bankactions.h"
#include "ui_bankactions.h"

BankActions::BankActions(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BankActions)
{
    ui->setupUi(this);
}

BankActions::~BankActions()
{
    delete ui;
}
