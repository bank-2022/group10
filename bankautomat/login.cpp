#include "login.h"
#include "ui_login.h"

Login::Login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);

}

Login::~Login()
{
    delete ui;
    ui=nullptr;
    delete objectPin;
    objectPin=nullptr;
}

void Login::on_btnLoginLogin_clicked()
{
    rfid=ui->lineEditRFID->text();
    objectPin = new Pin(rfid);
   objectPin->show();
   this->close();

}


