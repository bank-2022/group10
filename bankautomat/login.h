#ifndef LOGIN_H
#define LOGIN_H

#include "bankmain.h"
#include "myurl.h"

#include <QDialog>
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QJsonDocument>


namespace Ui {
class Login;
}

class Login : public QDialog
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();

private slots:
    void on_btnLoginLogin_clicked();
    void loginSlot(QNetworkReply *reply);

private:
    Ui::Login *ui;
    QString rfid;
    QString password;
    BankMain *objectBankMain;
    MyUrl *objectMyUrl;
    QString baseUrl;

    QNetworkAccessManager *loginManager;
    QNetworkReply *reply;
    QByteArray response_data;
};

#endif // LOGIN_H
