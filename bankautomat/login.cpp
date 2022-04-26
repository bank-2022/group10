#include "login.h"
#include "ui_login.h"

Login::Login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
  //  connect(pBankTimer,SIGNAL(timeout_signal()),
  //              this,SLOT(timeoutHandler()));

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

    connect(this,SIGNAL(timeReset_signal(states,events)),
                pBankTimer,SLOT(runStateMachine(states,events)));
    emit timeReset_signal(tier1,timeReset);
    disconnect(this,SIGNAL(timeReset_signal(states,events)),
                pBankTimer,SLOT(runStateMachine(states,events)));

    this->close();



}


