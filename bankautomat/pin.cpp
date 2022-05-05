#include "pin.h"
#include "ui_pin.h"

Pin::Pin(QString korttinumero, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Pin)
{
    ui->setupUi(this);


    rfid=korttinumero;
    qDebug() << rfid;
    ui->labelStatus->setText("Näppäile tunnusluku\n\nLopuksi paina OK");

    QPushButton *numButtons[10];
    for (int i=0;i<10;++i ) {
        QString buttonName="pushButton_"+QString::number(i);
        numButtons[i] = Pin::findChild<QPushButton *>(buttonName);
        connect(numButtons[i],SIGNAL(released()), this,
                SLOT(NumPressed()));



    }

}

Pin::~Pin()
{
    delete ui;
}



void Pin::NumPressed()
{
    QPushButton *button =(QPushButton *)sender();
    QString buttonValue = button->text();
    QString displayValue = ui->lineEditPin->text();
    emit pinBtnPress_signal();
    if(displayValue.isEmpty()){
        ui->lineEditPin->setText(buttonValue);
    }
    else {
        QString newVal = displayValue +buttonValue;
        ui->lineEditPin->setText(newVal);
    }
}

void Pin::on_pushButton_Cancel_clicked()
{
    emit pinCancel_signal();
    this->close();
}


void Pin::on_pushButton_Clear_clicked()
{
    QString text = ui->lineEditPin->text();
    text.chop(1);
    ui->lineEditPin->setText(text);
    emit pinBtnPress_signal();
}


void Pin::on_pushButton_OK_clicked()
{
    qDebug() <<"on_pushButton_OK_clicked()";
    pin=ui->lineEditPin->text();

    emit pin_signal(pin);
    qDebug() <<"pin lähetetty";
    emit pinOk_signal();
    qDebug() <<"pinOk signaali lähetetty";
}

void Pin::cardLocked_slot()
{
    ui->labelStatus->setText("Korttisi on lukittu. Ota yhteyttä pankkiin.");
    ui->frame->setEnabled(false);
    QTimer::singleShot(3000,this,SLOT(close()));
}

void Pin::loginSuccess_slot()
{
    this->close();
}

void Pin::wrongPin_slot()
{
    ui->lineEditPin->clear();
}

void Pin::attemptsLeft_slot(int attemptfail)
{
    ui->labelStatus->setText("Sinulla on "+QString::number(attemptfail)+" kirjautumisyritystä jäljellä");
    if (attemptfail==1){
      ui->labelStatus->setText("Sinulla on "+QString::number(attemptfail)+" kirjautumisyritys jäljellä");
    }
}

void Pin::timeoutPin_slot()
{
    this->close();
}


