#include "bankmain.h"
#include "ui_bankmain.h"

BankMain::BankMain(QString rfid, QByteArray token, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BankMain)
{
    ui->setupUi(this);

}

BankMain::~BankMain()
{
    delete ui;
}

void BankMain::nimi_slot(QString nimistr)
{
    ui->labelName->setText(nimistr);
    ui->labelName->adjustSize();
}

void BankMain::saldo_slot(QString saldostr)
{
    ui->labelSum->setText(saldostr);
    ui->labelSum->adjustSize();
}

void BankMain::tapahtumat_slot(QString tapahtumatstr)
{
    ui->MainActions->setText(tapahtumatstr);
}

void BankMain::saldoUpdate_slot(QString saldoUpdatestr)
{
    this->ui->labelSum->setText(saldoUpdatestr);
    ui->labelSum->adjustSize();
}

void BankMain::timeoutBankMain_slot()
{
    this->close();
}




void BankMain::on_buttonDrawMoney_clicked()
{
    emit drawMoney_signal();

}


void BankMain::on_buttonActions_clicked()
{
    emit bankActions_signal();

}


void BankMain::on_buttonLogOut_clicked()
{
    emit logOut_signal();
    this->close();
}





