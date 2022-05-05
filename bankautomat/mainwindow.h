#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "login.h"
#include "pin.h"
#include "myurl.h"
#include "bankmain.h"
#include "bankactions.h"
#include "drawmoney.h"
#include "drawanothersum.h"

#include <QString>
#include <QMainWindow>
#include <QSerialPort>
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QJsonDocument>
#include <QTimer>
#include <QModelIndex>

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


enum states
{
    loggedOut,              // tässä tilakoneen tilat, nimetty sen mukaan,
    enteringPin,            // millä kirjautumisasteella ne vaikuttavat.
    mainMenu,
    accDetails,
    drawing,
    specifying

};
enum events
{
    standBy,                // Alussa ollaan tässä.
    moveState,              // kun tasojen välillä liikutaan.
    moveState2,             // Tukemassa tasojen välillä liikkumista kun on useampi v/e
    timeReset,              // tällä resetataan aika
    timeStart,              // tällä käynnistetään ajastin.
    timerExpires,           // käsitellään välivaiheella ajan loppuminen.
    loggingOut              // poistutaan takaisin pohjatilaan
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void BankMainActions();

public slots:

    void login_slot();                      // loginia
    void korttinumero_slot(QString);

    void pin_slot(QString);                 // pinniä
    void pinOk_slot();
    void loginLogin_slot();

    void drawMoney_slot();                  // bankmainia
    void bankActions_slot();

    void btnActions_slot();                 // bankactionssia
    void btnPrev_slot();

    void runStateMachine(states,events);    // ajastinta
    void handleTimeout();
    void loggingIn_slot();
    void pinBtnPress_slot();
    void pinCancel_slot();
    void logOut_slot();
    void closeActions_slot();
    void moneyBtnPressed_slot();
    void moneyBtnClose_slot();
    void drawxBtnPressed_slot();

private slots:
    void on_btnLogin_clicked();             // loginia/mainwindowia
    void serialReadyRead();


    void pinSlot(QNetworkReply *reply);     // pinniä
    void loginSlot(QNetworkReply *reply2);

    void accountSlot(QNetworkReply *reply); // bankmainia
    void actionsSlot(QNetworkReply *reply);
    void updateSlot(QNetworkReply *reply);
    void updateBalance();

    void bankActionsSlot(QNetworkReply *reply); // bankactionssia

    void debitSlot(QNetworkReply *reply);   // drawmoneyta
    void btnDrawX_slot();
    void button_slot(float);


signals:
   //void timeStart_signal(states,events);

    void cardLocked_signal();               // pinniä
    void loginSuccess_signal();
    int attemptsLeft_signal(int);
    void wrongPin_signal();
    void loginLogin_signal();

    void nimi_signal(QString);              // bankmainia
    void saldo_signal(QString);
    void tapahtumat_signal(QString);
    void saldoUpdate_signal(QString);

    void actionsTapahtumat_signal(QString); // bankactionssia

    void drawSuccess_signal();              // drawmoneyta
    void drawFailure_signal();

    void timeReset_signal(states,events);   // ajastinta
    void timeStart_signal(states,events);
    void moveState_signal(states,events);
    void outOfTime_signal(states,events);
    void loggingOut_signal(states,events);
    void timeoutPin_signal();
    void timeoutBankMain_signal();
    void timeoutBankActions_signal();
    void timeoutDrawMoney_signal();
    void timeoutDrawAnotherSum_signal();



private:
    Ui::MainWindow *ui;
    QSerialPort *mSerial;
    Login *objectLogin;
    Pin *objectPin;
    MyUrl *objectMyUrl;
    BankMain *objectBankMain;
    BankActions *objectBankActions;
    DrawMoney *objectDrawMoney;
    DrawAnotherSum *objectDrawX;

    QString rfid;                           // loginia ja pinnniä
    QString pin;

    QString base_url;                       // pinniä ja kait myös bankmainia
    QNetworkAccessManager *pinManager;
    QNetworkAccessManager *loginManager;
    QNetworkReply *reply;
    QNetworkReply *reply2;
    QByteArray response_data;
    QByteArray webtoken;
    int loginAttempts = 2;
    int loginAttemptsLeft;
    int dbAttempts;

    MyUrl *objectMyUrl2;                    // bankmainia
    QNetworkAccessManager *accountManager;
    QNetworkAccessManager *actionsManager;
    QString korttinumero;
    QString id_tili;
    QString id_kortti;
    QString saldo;
    int ttSivu;

    QString tili_id;                        // bankactionssia

    QString kortti_id;                      // drawmoneyta
    QNetworkAccessManager *debitManager;
    QVector <QPushButton *> buttons;
    int sum;

    states State;                           // ajastinta
    events Event;
    QTimer timer;
    void loggedOutHandler(events e);
    void enteringPinHandler(events e);
    void mainMenuHandler(events e);
    void accDetailsHandler(events e);
    void drawingHandler(events e);
    void specifyingHandler(events e);



   // bankTimer * pBanktimer;
};
#endif // MAINWINDOW_H
