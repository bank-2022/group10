#include "login.h"
#include "ui_login.h"

Login::Login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);

    objectMyUrl=new MyUrl;
    baseUrl=objectMyUrl->getBaseUrl();
}

Login::~Login()
{
    delete ui;
    ui=nullptr;
    delete objectBankMain;
    objectBankMain=nullptr;
}

void Login::on_btnLoginLogin_clicked()
{
    qDebug() << "BaseUrl="+baseUrl;
    rfid=ui->lineEditRFID->text();
    password=ui->lineEditPassword->text();
    objectBankMain = new BankMain;
    objectBankMain->show();

    QJsonObject jsonObj;
    jsonObj.insert("korttinumero",rfid);
    jsonObj.insert("pin",password);


    QNetworkRequest request((baseUrl+"/login"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");


    loginManager = new QNetworkAccessManager(this);
    connect(loginManager, SIGNAL(finished (QNetworkReply*)), this, SLOT(loginSlot(QNetworkReply*)));

    reply = loginManager->post(request, QJsonDocument(jsonObj).toJson());
}

void Login::loginSlot(QNetworkReply *reply)
{
    response_data=reply->readAll();
    qDebug() << response_data;
}

