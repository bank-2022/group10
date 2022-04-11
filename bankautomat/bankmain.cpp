#include "bankmain.h"
#include "ui_bankmain.h"

BankMain::BankMain(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BankMain)
{
    ui->setupUi(this);
}

BankMain::~BankMain()
{
    delete ui;
}
