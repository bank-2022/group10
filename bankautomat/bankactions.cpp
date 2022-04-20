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

void BankActions::on_btnActionsNext_clicked()
{

}


void BankActions::on_btnActionsPrevious_clicked()
{

}


void BankActions::on_btnActionsClose_clicked()
{
 this->close();
}


void BankActions::on_listView_indexesMoved(const QModelIndexList &indexes)
{


}

