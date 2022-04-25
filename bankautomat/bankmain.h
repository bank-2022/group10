#ifndef BankMain_H
#define BankMain_H

#include "myurl.h"
#include "bankactions.h"
#include "drawmoney.h"

#include <QDialog>
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QJsonDocument>

namespace Ui {
class BankMain;
}

class BankMain : public QDialog
{
    Q_OBJECT

public:
    explicit BankMain(QString rfid, QByteArray token, QWidget *parent = nullptr);
    void BankMainActions();
    ~BankMain();

private slots:

    void accountSlot(QNetworkReply *reply);
    void actionsSlot(QNetworkReply *reply);
    void on_buttonDrawMoney_clicked();
    void on_buttonActions_clicked();
    void on_buttonLogOut_clicked();


private:
    Ui::BankMain *ui;
    MyUrl *objectMyUrl;
    MyUrl *objectMyUrl2;
    BankActions *objectBankActions;
    DrawMoney *objectDrawMoney;

    QNetworkAccessManager *accountManager;
    QNetworkAccessManager *actionsManager;
    QNetworkReply *reply;
    QByteArray response_data;
    QString korttinumero;
    QString id_tili;
    QString id_kortti;
    QString saldo;
    QByteArray webtoken;
    int ttSivu;
    int rivit;
};

#endif // BankMain_H
