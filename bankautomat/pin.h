#ifndef PIN_H
#define PIN_H

#include "bankmain.h"
#include "myurl.h"


#include <QDialog>
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QJsonDocument>
 #include <QTimer>

namespace Ui {
class Pin;
}

class Pin : public QDialog
{
    Q_OBJECT

public:
    explicit Pin(QString korttinumero, QWidget *parent = nullptr);
    ~Pin();

private slots:

    void on_pushButton_Cancel_clicked();
    void on_pushButton_Clear_clicked();
    void on_pushButton_OK_clicked();
    void NumPressed();

    void pinSlot(QNetworkReply *reply);

private:
    Ui::Pin *ui;
    QString rfid;
    QString pin;
    MyUrl *objectMyUrl;
    QString base_url;
    QNetworkAccessManager *pinManager;
    QNetworkReply *reply;
    QByteArray response_data;
    QByteArray webtoken;
    BankMain *objectBankMain;
    int loginAttempts = 3;

};

#endif // PIN_H
