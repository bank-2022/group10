#ifndef BANKACTIONS_H
#define BANKACTIONS_H

#include "myurl.h"

#include <QDialog>
#include <QModelIndex>
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QJsonDocument>


namespace Ui {
class BankActions;
}

class BankActions : public QDialog
{
    Q_OBJECT

public:
    explicit BankActions(QByteArray token,QWidget *parent = nullptr);
    ~BankActions();

private slots:
    void on_btnActionsNext_clicked();
    void on_btnActionsPrevious_clicked();
    void on_btnActionsClose_clicked();

    void actionsSlot(QNetworkReply *reply);

private:
    Ui::BankActions *ui;
    MyUrl *objectMyUrl;
    QString base_url;
    QNetworkAccessManager *actionsManager;
    QNetworkReply *reply;
    QByteArray response_data;
    QString korttinumero;
    QByteArray webtoken;
};

#endif // BANKACTIONS_H
