#include "mainwindow.h"
#include "ui_mainwindow.h"


/*************************************

  RAKENTAJA

**************************************/


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    objectLogin = new Login;
    mSerial = new QSerialPort(this);

    if (mSerial->isOpen()) {
        qDebug() << "Serial already connected, disconnecting!";
        mSerial->close();
    }

    mSerial->setPortName("com4");
    mSerial->setBaudRate(QSerialPort::Baud115200);
    mSerial->setDataBits(QSerialPort::Data8);
    mSerial->setParity(QSerialPort::NoParity);
    mSerial->setStopBits(QSerialPort::OneStop);
    mSerial->setFlowControl(QSerialPort::NoFlowControl);

    if(mSerial->open(QIODevice::ReadWrite)) {
        qDebug() << "SERIAL: OK!";
    } else {
        qDebug() << "SERIAL: ERROR!";
    }

    connect(mSerial, &QSerialPort::readyRead,
            this, &MainWindow::serialReadyRead);


/*************************************

    SIGNAALIT KLIKKIHÄNDLEREILLE

**************************************/


    connect(objectLogin,SIGNAL(login_signal()),
            this,SLOT(login_slot()));



    connect(objectLogin,SIGNAL(korttinumero_signal(QString)),
            this,SLOT(korttinumero_slot(QString)));



    connect(this,SIGNAL(loginLogin_signal()),
            this,SLOT(loginLogin_slot()));

    connect(objectLogin,SIGNAL(loggingIn_signal()),
            this,SLOT(loggingIn_slot()));


/*************************************

        SIGNAALIT AJASTIMELLE

**************************************/


    connect(this,SIGNAL(timeReset_signal(states,events)),
            this,SLOT(runStateMachine(states,events)));

    connect(this,SIGNAL(timeStart_signal(states,events)),
            this,SLOT(runStateMachine(states,events)));

    connect(this,SIGNAL(outOfTime_signal(states,events)),
            this,SLOT(runStateMachine(states,events)));

    connect(this,SIGNAL(moveState_signal(states,events)),
            this,SLOT(runStateMachine(states,events)));

    connect(this,SIGNAL(loggingOut_signal(states,events)),
            this,SLOT(runStateMachine(states,events)));

    connect(&this->timer,SIGNAL(timeout()),
            this,SLOT(handleTimeout()));

    State = loggedOut;
    Event = standBy;

    runStateMachine(State,Event);


}


/*************************************

  TUHOAJA

**************************************/


MainWindow::~MainWindow()
{
    delete ui;
    delete objectLogin;
    delete objectPin;
    delete objectBankMain;
    delete objectBankActions;
    delete objectDrawMoney;
    delete objectDrawX;
    ui=nullptr;
    objectLogin=nullptr;
    objectPin=nullptr;
}


/*************************************

  LOGIN NAPIN FUNKTIO

**************************************/


void MainWindow::on_btnLogin_clicked()
{
objectLogin->show();

}


/*************************************

  RFID LUKIJAN SLOTTI

**************************************/


void MainWindow::serialReadyRead()
{
    QString data = mSerial->readAll();
    rfid = data;
    rfid.remove(0,3);
    rfid.chop(3);
    qDebug() << rfid;
    objectPin = new Pin(rfid);
    objectPin->show();



    connect(objectPin,SIGNAL(pinBtnPress_signal()),
            this,SLOT(pinBtnPress_slot()));

    connect(objectPin,SIGNAL(pinCancel_signal()),
            this,SLOT(pinCancel_slot()));

    connect(objectPin,SIGNAL(pin_signal(QString)),
            this,SLOT(pin_slot(QString)));

    connect(objectPin,SIGNAL(pinOk_signal()),
            this,SLOT(pinOk_slot()));
}


/*************************************

  LOGIN-RUUDUN KLIKKIHÄNDLERI

**************************************/


void MainWindow::login_slot()
{
    qDebug() << "siirrytään pin-ruutuun!";

    objectPin = new Pin(rfid);

    connect(objectPin,SIGNAL(pinBtnPress_signal()),
            this,SLOT(pinBtnPress_slot()));

    connect(objectPin,SIGNAL(pinCancel_signal()),
            this,SLOT(pinCancel_slot()));

    connect(objectPin,SIGNAL(pinOk_signal()),
            this,SLOT(pinOk_slot()));

    connect(objectPin,SIGNAL(pin_signal(QString)),
            this,SLOT(pin_slot(QString)));

    connect(this,SIGNAL(loginSuccess_signal()),
            objectPin,SLOT(loginSuccess_slot()));

    objectPin->show();

    qDebug() << "koostetaan myurl!";
    objectMyUrl=new MyUrl;
    base_url=objectMyUrl->getBaseUrl();

}

void MainWindow::korttinumero_slot(QString rfidnro)
{
    rfid=rfidnro;
    qDebug() << "RFID vastaanotettu!"<<rfid;
}


/*************************************

  PIN                            PINNISSÄ ON JOKU ERRORI KUN LAITTAA VÄÄRÄN SALASANAN

**************************************/


void MainWindow::pin_slot(QString pinnro)
{
    pin=pinnro;
    qDebug() << "PIN vastaanotettu!"<<pin;
}

void MainWindow::pinOk_slot()
{
    qDebug() << "ok-painiketta painettu!";
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

void MainWindow::loginSlot(QNetworkReply *reply2)
{
    response_data=reply2->readAll();
    qDebug()<<rfid;
    qDebug() << response_data;
    dbAttempts=response_data.toInt();
    qDebug()<< "db attempts"<< dbAttempts;
    loginAttemptsLeft=loginAttempts-dbAttempts;
    qDebug()<< "db left"<<loginAttemptsLeft;
}


void MainWindow::pinSlot(QNetworkReply *reply)
{
    response_data=reply->readAll();
    qDebug() <<response_data;

    if (response_data =="cardLocked")
    {
         qDebug() <<"ERROR: card locked!";
         connect(this,SIGNAL(cardLocked_signal()),
                 objectPin,SLOT(cardLocked_slot()));
         emit cardLocked_signal();

    }
    else if (response_data!="false") {
        webtoken="Bearer "+response_data;

        emit loginLogin_signal();
        emit loginSuccess_signal();


    }
    else  {

        loginAttemptsLeft=loginAttempts-dbAttempts;
        qDebug() <<"ERROR";
        // loginAttempts--;
        qDebug() <<"Attempts left: "<<loginAttemptsLeft;

        connect(this,SIGNAL(wrongPin_signal()),
                objectPin,SLOT(wrongPin_slot()));
        emit wrongPin_signal();
        connect(this,SIGNAL(attemptsLeft_signal(int)),
                objectPin,SLOT(attemptsLeft_slot(int)));
        emit attemptsLeft_signal(loginAttemptsLeft);
        if (loginAttemptsLeft<1){
            qDebug() << "Too many invalid login attempts";
            connect(this,SIGNAL(cardLocked_signal()),
                    objectPin,SLOT(cardLocked_slot()));
            emit cardLocked_signal();
        }
    }
}


/*************************************

  PIN-RUUDUN KLIKKIHÄNDLERI

**************************************/


void MainWindow::loginLogin_slot()
{
    objectBankMain = new BankMain(rfid, webtoken);

    State = enteringPin;
    Event = moveState;
    emit moveState_signal(State,Event);

    connect(objectBankMain,SIGNAL(drawMoney_signal()),
            this,SLOT(drawMoney_slot()));
    connect(objectBankMain,SIGNAL(bankActions_signal()),
            this,SLOT(bankActions_slot()));
    connect(objectBankMain,SIGNAL(logOut_signal()),
            this,SLOT(logOut_slot()));

    objectBankMain->show();



    korttinumero=rfid;
    objectMyUrl=new MyUrl;
    objectMyUrl2=new MyUrl;
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


/*************************************

  BANKMAIN

**************************************/


void MainWindow::accountSlot(QNetworkReply *reply)
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

    connect(this,SIGNAL(nimi_signal(QString)),
            objectBankMain,SLOT(nimi_slot(QString)));
    connect(this,SIGNAL(saldo_signal(QString)),
            objectBankMain,SLOT(saldo_slot(QString)));
    emit nimi_signal(nimi);
    emit saldo_signal(saldo);




    BankMainActions();
}

void MainWindow::BankMainActions()
{
    QString site_url2=objectMyUrl2->getBaseUrl()+"/tilitapahtumat/get/"+id_tili+"/1/5";     //1.Sivu 5 ensimmäistä tilitapahtumaa
    QNetworkRequest request2((site_url2));
    request2.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    request2.setRawHeader(QByteArray("Authorization"),(webtoken));

    actionsManager = new QNetworkAccessManager(this);
    connect(actionsManager, SIGNAL(finished(QNetworkReply*)),this, SLOT(actionsSlot(QNetworkReply*)));
    reply = actionsManager->get(request2);
}

void MainWindow::actionsSlot(QNetworkReply *reply)
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
    connect(this,SIGNAL(tapahtumat_signal(QString)),
            objectBankMain,SLOT(tapahtumat_slot(QString)));
    emit tapahtumat_signal(tapahtumat);
}

void MainWindow::updateSlot(QNetworkReply *reply)
{
    response_data=reply->readAll();
    qDebug()<<response_data;

    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    QJsonArray json_array = json_doc.array();


    foreach (const QJsonValue &value, json_array) {
        QJsonObject json_obj = value.toObject();
        saldo+=QString::number(json_obj["saldo"].toInt());
    }
    connect(this,SIGNAL(saldoUpdate_signal(QString)),
            objectBankMain,SLOT(saldoUpdate_slot(QString)));
    emit saldoUpdate_signal(saldo);
    BankMainActions();
}

void MainWindow::updateBalance()
{
    QString site_url=objectMyUrl->getBaseUrl()+"/asiakas/tili/"+korttinumero;
    QNetworkRequest request((site_url));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");


    //WEBTOKEN ALKU
    request.setRawHeader(QByteArray("Authorization"),(webtoken));
    //WEBTOKEN LOPPU

    accountManager = new QNetworkAccessManager(this);
    connect(accountManager, SIGNAL(finished(QNetworkReply*)),this, SLOT(updateSlot(QNetworkReply*)));
    reply = accountManager->get(request);
}


/*************************************

  BANKMAIN-RUUDUN KLIKKIHÄNDLERI

**************************************/

void MainWindow::drawMoney_slot()
{
    objectDrawMoney = new DrawMoney(id_kortti, id_tili, webtoken);

    State = mainMenu;
    Event = moveState2;
    emit moveState_signal(State,Event);

    objectMyUrl=new MyUrl;
    base_url=objectMyUrl->getBaseUrl();
    kortti_id=id_kortti;
    tili_id=id_tili;

    connect(objectDrawMoney, SIGNAL(updateSignal()),
            this, SLOT(updateBalance()));
    connect(objectDrawMoney, SIGNAL(btnDrawX_signal()),
            this, SLOT(btnDrawX_slot()));
    connect(objectDrawMoney, SIGNAL(moneyBtnPressed_signal()),
            this, SLOT(moneyBtnPressed_slot()));
    connect(objectDrawMoney, SIGNAL(moneyBtnClose_signal()),
            this, SLOT(moneyBtnClose_slot()));
    connect(objectDrawMoney, SIGNAL(button_signal(float)),
            this, SLOT(button_slot(float)));

    objectDrawMoney->show();
    saldo=QString();
}

void MainWindow::bankActions_slot()
{
    objectBankActions = new BankActions(id_tili,webtoken);

    State = mainMenu;
    Event = moveState;
    emit moveState_signal(State,Event);

    objectMyUrl=new MyUrl;
    tili_id = id_tili;
    ttSivu = 1;

    QString site_url=objectMyUrl->getBaseUrl()+"/tilitapahtumat/get/"+tili_id+"/"+QString::number(ttSivu)+"/10";
    QNetworkRequest request((site_url));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    //WEBTOKEN ALKU
    request.setRawHeader(QByteArray("Authorization"),(webtoken));
    //WEBTOKEN LOPPU

    actionsManager = new QNetworkAccessManager(this);
    connect(actionsManager, SIGNAL(finished(QNetworkReply*)),this, SLOT(bankActionsSlot(QNetworkReply*)));
    reply = actionsManager->get(request);




    objectBankActions->show();
}





/*************************************

  BANKACTIONS

**************************************/


void MainWindow::bankActionsSlot(QNetworkReply *reply)
{
    response_data = reply->readAll();
    qDebug() << response_data;

    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    QJsonArray json_array = json_doc.array();
    QString actionsTapahtumat;
    foreach (const QJsonValue &value, json_array){
        QJsonObject json_obj = value.toObject();
        actionsTapahtumat+=json_obj["paivays"].toString()+" "+json_obj["tapahtuma"].toString()+" "+QString::number(json_obj["summa"].toInt())+"\r";
}

    qDebug()<< actionsTapahtumat;
    connect(this,SIGNAL(actionsTapahtumat_signal(QString)),
            objectBankActions,SLOT(actionsTapahtumat_slot(QString)));
    connect(objectBankActions,SIGNAL(btnActions_signal()),
            this,SLOT(btnActions_slot()));
    connect(objectBankActions,SIGNAL(btnPrev_signal()),
            this,SLOT(btnPrev_slot()));
    connect(objectBankActions,SIGNAL(closeActions_signal()),
            this,SLOT(closeActions_slot()));

    emit actionsTapahtumat_signal(actionsTapahtumat);
}

void MainWindow::btnActions_slot()
{
    State = accDetails;
    Event = timeReset;
    emit timeReset_signal(State,Event);

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
    connect(actionsManager, SIGNAL(finished(QNetworkReply*)),this, SLOT(bankActionsSlot(QNetworkReply*)));
    reply = actionsManager->get(request);
}

void MainWindow::btnPrev_slot()
{
    State = accDetails;
    Event = timeReset;
    emit timeReset_signal(State,Event);

    ttSivu = ttSivu + 1;
    QString site_url=objectMyUrl->getBaseUrl()+"/tilitapahtumat/get/"+tili_id+"/"+QString::number(ttSivu)+"/10";
    QNetworkRequest request((site_url));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    //WEBTOKEN ALKU
    request.setRawHeader(QByteArray("Authorization"),(webtoken));
    //WEBTOKEN LOPPU

    actionsManager = new QNetworkAccessManager(this);
    connect(actionsManager, SIGNAL(finished(QNetworkReply*)),this, SLOT(bankActionsSlot(QNetworkReply*)));
    reply = actionsManager->get(request);
    qDebug() << ttSivu;
}


/*************************************

  DRAWMONEY

**************************************/


void MainWindow::button_slot(float summa)
{
    qDebug() <<summa;
    qDebug() <<kortti_id;
    qDebug() <<tili_id;
    qDebug() <<summa;
    QJsonObject jsonObj;
    jsonObj.insert("id_kortti",kortti_id);
    jsonObj.insert("id_tili",tili_id);
    jsonObj.insert("summa",summa);

    QNetworkRequest request((base_url+"/tilitapahtumat/debit"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    request.setRawHeader(QByteArray("Authorization"),(webtoken));


    debitManager = new QNetworkAccessManager(this);
    connect(debitManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(debitSlot(QNetworkReply*)));

    reply = debitManager->post(request, QJsonDocument(jsonObj).toJson());
}


void MainWindow::debitSlot(QNetworkReply *reply)
{
    response_data=reply->readAll();
    qDebug() <<response_data;

    if(response_data == "1"){
        qDebug() <<"OK";
        connect(this,SIGNAL(drawSuccess_signal()),
                objectDrawMoney,SLOT(drawSuccess_slot()));
        emit drawSuccess_signal();
    }
    else {
        qDebug() <<"ERROR";
        connect(this,SIGNAL(drawFailure_signal()),
                objectDrawMoney,SLOT(drawFailure_slot()));
        emit drawFailure_signal();
    }
}


/*************************************

  DRAWANOTHERSUM

**************************************/


void MainWindow::btnDrawX_slot()
{
    State = drawing;
    Event = moveState2;
    emit moveState_signal(State,Event);

    objectDrawX = new DrawAnotherSum;
    DrawAnotherSum dialog;
    connect(objectDrawX,SIGNAL(drawxBtnPressed_signal()),
            this,SLOT(drawxBtnPressed_slot()));

    if (dialog.exec() == QDialog::Rejected) {

        State = specifying;
        Event = moveState;
        emit moveState_signal(State,Event);

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


/*************************************

  AJASTIN

**************************************/


void MainWindow::runStateMachine(states s, events e)
{
    switch (s) {

        case loggedOut:
            loggedOutHandler(e);
        break;

        case enteringPin:
            enteringPinHandler(e);
        break;

        case mainMenu:
            mainMenuHandler(e);
        break;

        case accDetails:
            accDetailsHandler(e);
        break;

        case drawing:
            drawingHandler(e);
        break;

        case specifying:
            specifyingHandler(e);
        break;

        default:
            qDebug()<<"State = "<<State<<" and event = "<< e;

    }
}

void MainWindow::handleTimeout()
{
    if(State == enteringPin)
    {
        State = enteringPin;
        Event = timerExpires;
    }
    else if(State == mainMenu)
    {
        State = mainMenu;
        Event = timerExpires;
    }
    else if(State == accDetails)
    {
        State = accDetails;
        Event = timerExpires;
    }
    else if(State == drawing)
    {
        State = drawing;
        Event = timerExpires;
    }
    else if(State == specifying)
    {
        State = specifying;
        Event = timerExpires;
    }

    else
    {
        qDebug()<<"...Error In Handling Timeout...";
    }

    runStateMachine(State,Event);
}

void MainWindow::loggedOutHandler(events e)
{
    if(e == standBy)
    {

        qDebug()<<"...System Standing By...";


    }
    else if(e == moveState)
    {
        qDebug()<<"...Starting Login...";
        State = enteringPin;
        Event = timeStart;
        emit moveState_signal(State,Event);
    }
    else
    {
        qDebug()<<"Wrong event in this state = "<<State<<" Event = "<<e;
    }
}

void MainWindow::enteringPinHandler(events e)
{
    if(e == timeStart)
    {
        qDebug()<<"...Starting Timer...";
        timer.start(10000);
    }
    else if(e == timeReset)
    {
        qDebug()<<"...User Activity detected On PIN...";
        timer.stop();
        State = enteringPin;
        Event = timeStart;
        emit timeReset_signal(State,Event);
    }
    else if(e == timerExpires)
    {
        timer.stop();
        qDebug()<<"...User Inactive, Dropping To Standby...";
        State = loggedOut;
        Event = standBy;
        emit outOfTime_signal(State,Event);
        connect(this,SIGNAL(timeoutPin_signal()),
                objectPin,SLOT(timeoutPin_slot()));
        emit timeoutPin_signal();
    }

    else if(e == moveState)
    {
        timer.stop();
        qDebug()<<"...Login Succesful...";
        State = mainMenu;
        Event = timeStart;
        emit moveState_signal(State,Event);
    }
    else if(e == loggingOut)
    {
        timer.stop();
        qDebug()<<"...Returning To Standby...";
        State = loggedOut;
        Event = standBy;
        emit loggingOut_signal(State,Event);
    }
    else
    {
        qDebug()<<"Wrong event in this state = "<<State<<" Event = "<<e;
    }
}

void MainWindow::mainMenuHandler(events e)
{
    if(e == timeStart)
    {
        qDebug()<<"...Starting Timer...";
        timer.start(30000);
    }

    else if(e == timerExpires)
    {
        timer.stop();
        qDebug()<<"...User Inactive, Dropping To Standby...";
        State = loggedOut;
        Event = standBy;
        emit outOfTime_signal(State,Event);
        connect(this,SIGNAL(timeoutBankMain_signal()),
                objectBankMain,SLOT(timeoutBankMain_slot()));
        emit timeoutBankMain_signal();
    }

    else if(e == moveState)
    {
        timer.stop();
        qDebug()<<"...User Moving On To Account History...";
        State = accDetails;
        Event = timeStart;
        emit moveState_signal(State,Event);
    }
    else if(e == moveState2)
    {
        timer.stop();
        qDebug()<<"...User Moving On To Drawing Money Out...";
        State = drawing;
        Event = timeStart;
        emit moveState_signal(State,Event);
    }
    else if(e == loggingOut)
    {
        timer.stop();
        qDebug()<<"...User Logging Out...";
        State = loggedOut;
        Event = standBy;
        emit moveState_signal(State,Event);
    }
    else
    {
        qDebug()<<"Wrong event in this state = "<<State<<" Event = "<<e;
    }
}

void MainWindow::accDetailsHandler(events e)
{
    if(e == timeStart)
    {
        qDebug()<<"...Starting Timer...";
        timer.start(10000);
    }
    else if(e == timeReset)
    {
        qDebug()<<"...User Activity detected On Account History...";
        timer.stop();
        State = accDetails;
        Event = timeStart;
        emit timeReset_signal(State,Event);
    }
    else if(e == timerExpires)
    {
        timer.stop();
        qDebug()<<"...User Inactive, Dropping To Main...";
        State = mainMenu;
        Event = timeStart;
        emit outOfTime_signal(State,Event);
        connect(this,SIGNAL(timeoutBankActions_signal()),
                objectBankActions,SLOT(timeoutBankActions_slot()));
        emit timeoutBankActions_signal();
    }

    else if(e == moveState)
    {
        timer.stop();
        qDebug()<<"...User Returning To Main...";
        State = mainMenu;
        Event = timeStart;
        emit moveState_signal(State,Event);
    }
    else
    {
        qDebug()<<"Wrong event in this state = "<<State<<" Event = "<<e;
    }
}

void MainWindow::drawingHandler(events e)
{
    if(e == timeStart)
    {
        qDebug()<<"...Starting Timer...";
        timer.start(10000);
    }
    else if(e == timeReset)
    {
        qDebug()<<"...User Activity detected On Sum Selector...";
        timer.stop();
        State = drawing;
        Event = timeStart;
        emit timeReset_signal(State,Event);
    }
    else if(e == timerExpires)
    {
        timer.stop();
        qDebug()<<"...User Inactive, Dropping To Main...";
        State = mainMenu;
        Event = timeStart;
        emit outOfTime_signal(State,Event);
        connect(this,SIGNAL(timeoutDrawMoney_signal()),
                objectDrawMoney,SLOT(timeoutDrawMoney_slot()));
        emit timeoutDrawMoney_signal();
    }

    else if(e == moveState)
    {
        timer.stop();
        qDebug()<<"...User Returning To Main...";
        State = mainMenu;
        Event = timeStart;
        emit moveState_signal(State,Event);
    }
    else if(e == moveState2)
    {
        timer.stop();
        qDebug()<<"...User Moving On To Specify Amount...";
        State = specifying;
        Event = timeStart;
        emit moveState_signal(State,Event);
    }
    else
    {
        qDebug()<<"Wrong event in this state = "<<State<<" Event = "<<e;
    }
}

void MainWindow::specifyingHandler(events e)
{
    if(e == timeStart)
    {
        qDebug()<<"...Starting Timer...";
        timer.start(10000);
    }
    else if(e == timerExpires)
    {
        timer.stop();
        qDebug()<<"...User Inactive, Dropping To Picking Money Or Stuff...";
        State = specifying;
        Event = moveState;
        emit outOfTime_signal(State,Event);
        connect(this,SIGNAL(timeoutDrawAnotherSum_signal()),
                objectDrawX,SLOT(timeoutDrawAnotherSum_slot()));
        emit timeoutDrawAnotherSum_signal();
    }

    else if(e == moveState)
    {
        timer.stop();
        qDebug()<<"...User Returning To Picking An Amount...";
        State = drawing;
        Event = timeStart;
        emit moveState_signal(State,Event);
    }

    else
    {
        qDebug()<<"Wrong event in this state = "<<State<<" Event = "<<e;
    }
}

void MainWindow::loggingIn_slot()   // mennään pinniin
{
    State = loggedOut;
    Event = moveState;
    emit moveState_signal(State,Event);
}

void MainWindow::pinBtnPress_slot() // painetaan mitään pinnissä paikallaan
{
    State = enteringPin;
    Event = timeReset;
    emit timeReset_signal(State,Event);

}

void MainWindow::pinCancel_slot()   // palataan pinnistä
{
    State = enteringPin;
    Event = loggingOut;
    emit loggingOut_signal(State,Event);
}

void MainWindow::logOut_slot()      // kirjaudutaan ulos bankmainista
{
    State = mainMenu;
    Event = loggingOut;
    emit loggingOut_signal(State,Event);
}

void MainWindow::closeActions_slot()    // suljetaan bank actions
{
    State = accDetails;
    Event = moveState;
    emit moveState_signal(State,Event);
}

void MainWindow::moneyBtnPressed_slot() // painetaan nappia draw moneyssa
{
    State = drawing;
    Event = timeReset;
    emit timeReset_signal(State,Event);
}

void MainWindow::moneyBtnClose_slot()   // suljetaan draw money
{
    State = drawing;
    Event = moveState;
    emit moveState_signal(State,Event);
}

void MainWindow::drawxBtnPressed_slot() // painetaan nappia draw another summissa
{
    State = specifying;
    Event = moveState;
    emit moveState_signal(State,Event);
}
