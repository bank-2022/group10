#include "drawmoney.h"
#include "ui_drawmoney.h"

DrawMoney::DrawMoney(QString id_kortti, QString id_tili, QByteArray token, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DrawMoney)
{
    ui->setupUi(this);
    setModal(true);
    objectMyUrl=new MyUrl;
    base_url=objectMyUrl->getBaseUrl();
    kortti_id=id_kortti;
    tili_id=id_tili;
    webtoken=token;
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
    DrawAnotherSum dialog(this);


    if (dialog.exec() == QDialog::Rejected) {
        return;
    }

    sum=dialog.sum().toFloat();
    sum*=-1;

    qDebug() <<sum;
    qDebug() <<kortti_id;
    qDebug() <<tili_id;
    qDebug() <<sum;
    QJsonObject jsonObj;
    jsonObj.insert("id_kortti",kortti_id);
    jsonObj.insert("id_tili",tili_id);
    jsonObj.insert("summa",sum);

    QNetworkRequest request((base_url+"/tilitapahtumat/debit"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    request.setRawHeader(QByteArray("Authorization"),(webtoken));


    debitManager = new QNetworkAccessManager(this);
    connect(debitManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(debitSlot(QNetworkReply*)));

    reply = debitManager->post(request, QJsonDocument(jsonObj).toJson());

}


void DrawMoney::buttonClicked()
{
    QPushButton *button =(QPushButton *)sender();
    sum = button->text().toFloat();
    sum*=-1;

    qDebug() <<sum;
    qDebug() <<kortti_id;
    qDebug() <<tili_id;
    qDebug() <<sum;
    QJsonObject jsonObj;
    jsonObj.insert("id_kortti",kortti_id);
    jsonObj.insert("id_tili",tili_id);
    jsonObj.insert("summa",sum);

    QNetworkRequest request((base_url+"/tilitapahtumat/debit"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    request.setRawHeader(QByteArray("Authorization"),(webtoken));


    debitManager = new QNetworkAccessManager(this);
    connect(debitManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(debitSlot(QNetworkReply*)));

    reply = debitManager->post(request, QJsonDocument(jsonObj).toJson());
}


void DrawMoney::debitSlot(QNetworkReply *reply)
{
    response_data=reply->readAll();
    qDebug() <<response_data;

    if(response_data == "1"){
        qDebug() <<"OK";
        ui->labelStatus->setText("Ota rahat, ole hyvä");
    }
    else {
        qDebug() <<"ERROR";
        ui->labelStatus->setText("Nosto epäonnistui");
    }

}

void DrawMoney::on_btnDrawClose_clicked()
{
    emit updateSignal();
    this->close();
}




