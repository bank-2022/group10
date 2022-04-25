#include "bankmain.h"
#include "ui_bankmain.h"


BankMain::BankMain(QString rfid, QByteArray token, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BankMain)
{
    ui->setupUi(this);
    korttinumero=rfid;
    objectMyUrl=new MyUrl;
    objectMyUrl2=new MyUrl;
    webtoken=token;
    QString site_url=objectMyUrl->getBaseUrl()+"/asiakas/tili/"+korttinumero;
    QNetworkRequest request((site_url));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");


    //WEBTOKEN ALKU
    request.setRawHeader(QByteArray("Authorization"),(webtoken));
    //WEBTOKEN LOPPU

    accountManager = new QNetworkAccessManager(this);
    connect(accountManager, SIGNAL(finished(QNetworkReply*)),this, SLOT(accountSlot(QNetworkReply*)));
    reply = accountManager->get(request);
}

BankMain::~BankMain()
{
    delete ui;
}

void BankMain::accountSlot(QNetworkReply *reply)
{
    response_data=reply->readAll();
    qDebug()<<response_data;

    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    QJsonArray json_array = json_doc.array();
    QString nimi;
    foreach (const QJsonValue &value, json_array) {
        QJsonObject json_obj = value.toObject();
        nimi+=json_obj["nimi"].toString()+"\r";
    }

    foreach (const QJsonValue &value, json_array) {
        QJsonObject json_obj = value.toObject();
        saldo+=QString::number(json_obj["saldo"].toInt())+"\r";
    }
    foreach (const QJsonValue &value, json_array) {
        QJsonObject json_obj = value.toObject();
        id_kortti+=QString::number(json_obj["id_kortti"].toInt());
    }

    foreach (const QJsonValue &value, json_array) {
        QJsonObject json_obj = value.toObject();
        id_tili+=QString::number(json_obj["id_tili"].toInt());
    }


    qDebug()<<nimi<<id_kortti<<id_tili;

    ui->labelName->setText(nimi);
    ui->labelName->adjustSize();

    ui->labelSum->setText(saldo);
    ui->labelSum->adjustSize();
    BankMainActions();
}
void BankMain::BankMainActions()
{
    QString site_url2=objectMyUrl2->getBaseUrl()+"/tilitapahtumat/"+id_tili;
    QNetworkRequest request2((site_url2));
    request2.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    request2.setRawHeader(QByteArray("Authorization"),(webtoken));

    actionsManager = new QNetworkAccessManager(this);
    connect(actionsManager, SIGNAL(finished(QNetworkReply*)),this, SLOT(actionsSlot(QNetworkReply*)));
    reply = actionsManager->get(request2);
}


void BankMain::actionsSlot(QNetworkReply *reply)
{
    response_data = reply->readAll();
    qDebug() << response_data;

    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    QJsonArray json_array = json_doc.array();
    QString tapahtumat;
    foreach (const QJsonValue &value, json_array){
        QJsonObject json_obj = value.toObject();
        tapahtumat+=json_obj["paivays"].toString()+" "+json_obj["tapahtuma"].toString()+" "+QString::number(json_obj["summa"].toInt())+"\r";
}
    qDebug()<< tapahtumat;
    ui->MainActions->setText(tapahtumat);
}

void BankMain::on_buttonDrawMoney_clicked()
{
    objectDrawMoney = new DrawMoney(id_kortti, id_tili, webtoken);
    objectDrawMoney->show();
}


void BankMain::on_buttonActions_clicked()
{
    objectBankActions = new BankActions(id_tili,webtoken);
    objectBankActions->show();
}


void BankMain::on_buttonLogOut_clicked()
{
    this->close();
}




