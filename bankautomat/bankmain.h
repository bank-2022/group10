#ifndef BankMain_H
#define BankMain_H

#include "myurl.h"

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

private:
    Ui::BankMain *ui;
    MyUrl *objectMyUrl;

    QNetworkAccessManager *accountManager;
    QNetworkReply *reply;
    QByteArray response_data;
    QString korttinumero;
    QByteArray webtoken;
};

#endif // BankMain_H
