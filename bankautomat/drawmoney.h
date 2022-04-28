#ifndef DRAWMONEY_H
#define DRAWMONEY_H

#include "myurl.h"
#include "drawanothersum.h"

#include <QDialog>
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QJsonDocument>

namespace Ui {
class DrawMoney;
}

class DrawMoney : public QDialog
{
    Q_OBJECT

public:
    explicit DrawMoney(QString id_kortti, QString id_tili, QByteArray token, QWidget *parent = nullptr);
    ~DrawMoney();

signals:
    void updateSignal();

private slots:
    void debitSlot(QNetworkReply *reply);
    void buttonClicked();
    void on_btnDrawClose_clicked();
    void on_btnDrawX_clicked();

private:
    Ui::DrawMoney *ui;
    QString kortti_id;
    QString tili_id;
    MyUrl *objectMyUrl;
    QString base_url;
    QNetworkAccessManager *debitManager;
    QNetworkReply *reply;
    QByteArray response_data;
    QByteArray webtoken;
    QVector <QPushButton *> buttons;
    int sum;
};

#endif // DRAWMONEY_H
