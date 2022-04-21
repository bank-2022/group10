#include "bankmain.h"
#include "ui_bankmain.h"


BankMain::BankMain(QString rfid, QByteArray token, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BankMain)
{
    ui->setupUi(this);
    korttinumero=rfid;
    objectMyUrl=new MyUrl;
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

    QString saldo;
    foreach (const QJsonValue &value, json_array) {
        QJsonObject json_obj = value.toObject();
        saldo+=QString::number(json_obj["saldo"].toInt())+"\r";
    }


    qDebug()<<nimi;

    ui->labelName->setText(nimi);
    ui->labelName->adjustSize();

    ui->labelSum->setText(saldo);
    ui->labelSum->adjustSize();
}

void BankMain::on_buttonDrawMoney_clicked()
{
    objectDrawMoney = new DrawMoney;
    objectDrawMoney->show();
}


void BankMain::on_buttonActions_clicked()
{
    objectBankActions = new BankActions(webtoken);
    objectBankActions->show();
}


void BankMain::on_buttonLogOut_clicked()
{
    this->close();
}




void BankMain::on_listViewActions_indexesMoved(const QModelIndexList &indexes)
{

}

