#include "bankactions.h"
#include "ui_bankactions.h"

BankActions::BankActions(QString id_tili,QByteArray token,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BankActions)
{
    ui->setupUi(this);


}

BankActions::~BankActions()
{
    delete ui;
}

void BankActions::actionsTapahtumat_slot(QString actionsTapahtumat)
{
    ui->BankActionScreen->setText(actionsTapahtumat);
}

void BankActions::timeoutBankActions_slot()
{
    this->close();

}

void BankActions::on_btnActionsNext_clicked()
{
    emit btnActions_signal();
}


void BankActions::on_btnActionsPrevious_clicked()
{
    emit btnPrev_signal();
}


void BankActions::on_btnActionsClose_clicked()
{
    emit closeActions_signal();
    this->close();
}



