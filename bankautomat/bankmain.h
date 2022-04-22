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
    ~BankMain();

private slots:

    void accountSlot(QNetworkReply *reply);
    void on_buttonDrawMoney_clicked();
    void on_buttonActions_clicked();
    void on_buttonLogOut_clicked();
    void on_listViewActions_indexesMoved(const QModelIndexList &indexes);

private:
    Ui::BankMain *ui;
    MyUrl *objectMyUrl;    
    BankActions *objectBankActions;
    DrawMoney *objectDrawMoney;

    QNetworkAccessManager *accountManager;
    QNetworkReply *reply;
    QByteArray response_data;
    QString korttinumero;
    QString id_tili;
    QString id_kortti;
    QString saldo;
    QByteArray webtoken;
};

#endif // BankMain_H
