#include "pin.h"
#include "ui_pin.h"

Pin::Pin(QString korttinumero, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Pin)
{
    ui->setupUi(this);
    objectMyUrl=new MyUrl;
    base_url=objectMyUrl->getBaseUrl();
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
    this->close();
}


void Pin::on_pushButton_Clear_clicked()
{
    QString text = ui->lineEditPin->text();
    text.chop(1);
    ui->lineEditPin->setText(text);
}


void Pin::on_pushButton_OK_clicked()
{
    qDebug() <<"on_pushButton_OK_clicked()";
    pin=ui->lineEditPin->text();
    QJsonObject jsonObj;
    jsonObj.insert("korttinumero",rfid);
    jsonObj.insert("pin",pin);

    QNetworkRequest request((base_url+"/login"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    pinManager = new QNetworkAccessManager(this);
    connect(pinManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(pinSlot(QNetworkReply*)));

    reply = pinManager->post(request, QJsonDocument(jsonObj).toJson());

    QNetworkRequest request2((base_url+"/login/logintries/"+rfid));
    request2.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    loginManager = new QNetworkAccessManager(this);
    connect(loginManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(loginSlot(QNetworkReply*)));

    reply2 = loginManager->get(request2);
}

void Pin::loginSlot(QNetworkReply *reply2)
{
 response_data=reply2->readAll();
 qDebug()<<rfid;
 qDebug() << response_data;
 dbAttempts=response_data.toInt();
 qDebug()<< "db attempts"<< dbAttempts;
 loginAttemptsLeft=loginAttempts-dbAttempts;
 qDebug()<< "db left"<<loginAttemptsLeft;


}

void Pin::pinSlot(QNetworkReply *reply)
{
    response_data=reply->readAll();
    qDebug() <<response_data;

    if (response_data =="cardLocked")
    {
         qDebug() <<"ERROR: card locked!";
         ui->labelStatus->setText("Korttisi on lukittu. Ota yhteyttä pankkiin.");
         ui->frame->setEnabled(false);
         QTimer::singleShot(3000,this,SLOT(close()));
    }
    else if (response_data!="false") {
        webtoken="Bearer "+response_data;

        objectBankMain = new BankMain(rfid, webtoken);

        objectBankMain->show();
        this->close();
    }
    else  {
        ui->lineEditPin->clear();
        loginAttemptsLeft=loginAttempts-dbAttempts;
        qDebug() <<"ERROR";
        // loginAttempts--;
        qDebug() <<"Attempts left: "<<loginAttemptsLeft;
        ui->labelStatus->setText("Sinulla on "+QString::number(loginAttemptsLeft)+" kirjautumisyritystä jäljellä");
        if (loginAttemptsLeft==1){
          ui->labelStatus->setText("Sinulla on "+QString::number(loginAttemptsLeft)+" kirjautumisyritys jäljellä");
        }
        if (loginAttemptsLeft<1){
            qDebug() << "Too many invalid login attempts";
            ui->labelStatus->setText("Korttisi on lukittu. Ota yhteyttä pankkiin.");
            ui->frame->setEnabled(false);
            QTimer::singleShot(3000,this,SLOT(close()));
        }
    }
}


