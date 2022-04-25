#include "bankactions.h"
#include "ui_bankactions.h"

BankActions::BankActions(QString id_tili,QByteArray token,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BankActions)
{
    ui->setupUi(this);
    objectMyUrl=new MyUrl;
    webtoken=token;
    tili_id = id_tili;

    QString site_url=objectMyUrl->getBaseUrl()+"/tilitapahtumat/get/"+tili_id+"/"+QString::number(ttSivu)+"/10";
    QNetworkRequest request((site_url));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    //WEBTOKEN ALKU
    request.setRawHeader(QByteArray("Authorization"),(webtoken));
    //WEBTOKEN LOPPU

    actionsManager = new QNetworkAccessManager(this);
    connect(actionsManager, SIGNAL(finished(QNetworkReply*)),this, SLOT(actionsSlot(QNetworkReply*)));
    reply = actionsManager->get(request);


}

BankActions::~BankActions()
{
    delete ui;
}

void BankActions::on_btnActionsNext_clicked()
{
    ttSivu = ttSivu - 1;
    if(ttSivu == 0){
        ttSivu =1;
    }
 qDebug() << ttSivu;
 QString site_url=objectMyUrl->getBaseUrl()+"/tilitapahtumat/get/"+tili_id+"/"+QString::number(ttSivu)+"/10";
 QNetworkRequest request((site_url));
 request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

 //WEBTOKEN ALKU
 request.setRawHeader(QByteArray("Authorization"),(webtoken));
 //WEBTOKEN LOPPU

 actionsManager = new QNetworkAccessManager(this);
 connect(actionsManager, SIGNAL(finished(QNetworkReply*)),this, SLOT(actionsSlot(QNetworkReply*)));
 reply = actionsManager->get(request);
}


void BankActions::on_btnActionsPrevious_clicked()
{
  ttSivu = ttSivu + 1;
  QString site_url=objectMyUrl->getBaseUrl()+"/tilitapahtumat/get/"+tili_id+"/"+QString::number(ttSivu)+"/10";
  QNetworkRequest request((site_url));
  request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

  //WEBTOKEN ALKU
  request.setRawHeader(QByteArray("Authorization"),(webtoken));
  //WEBTOKEN LOPPU

  actionsManager = new QNetworkAccessManager(this);
  connect(actionsManager, SIGNAL(finished(QNetworkReply*)),this, SLOT(actionsSlot(QNetworkReply*)));
  reply = actionsManager->get(request);
  qDebug() << ttSivu;
}


void BankActions::on_btnActionsClose_clicked()
{

 this->close();
}

void BankActions::actionsSlot(QNetworkReply *reply)
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
    ui->BankActionScreen->setText(tapahtumat);
}


