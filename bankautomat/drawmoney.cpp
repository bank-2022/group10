#include "drawmoney.h"
#include "ui_drawmoney.h"

DrawMoney::DrawMoney(QString id_kortti, QString id_tili, QByteArray token, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DrawMoney)
{
    ui->setupUi(this);
    setModal(true);

    ui->labelStatus->setText("Valitse summa");

    buttons.append(ui->btnDraw20);
    buttons.append(ui->btnDraw40);
    buttons.append(ui->btnDraw60);
    buttons.append(ui->btnDraw100);
    buttons.append(ui->btnDraw200);
    buttons.append(ui->btnDraw500);

    foreach (QPushButton *ptr, buttons){
    connect(ptr,SIGNAL(released()), this,
            SLOT(buttonClicked()));}


}

DrawMoney::~DrawMoney()
{
    delete ui;
}



void DrawMoney::on_btnDrawX_clicked()
{

    emit btnDrawX_signal();



}


void DrawMoney::buttonClicked()
{
    QPushButton *button =(QPushButton *)sender();
    sum = button->text().toFloat();
    sum*=-1;

    emit moneyBtnPressed_signal();
    emit button_signal(sum);
}

void DrawMoney::drawSuccess_slot()
{
    ui->labelStatus->setText("Ota rahat, ole hyvä");
}

void DrawMoney::drawFailure_slot()
{
    ui->labelStatus->setText("Nosto epäonnistui");
}

void DrawMoney::timeoutDrawMoney_slot()
{
    this->close();

}


void DrawMoney::on_btnDrawClose_clicked()
{
    emit moneyBtnClose_signal();
    emit updateSignal();
    this->close();
}




