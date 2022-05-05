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
    explicit BankActions(QString id_tili,QByteArray token,QWidget *parent = nullptr);
    ~BankActions();

signals:
    void btnActions_signal();
    void btnPrev_signal();
    void closeActions_signal();

public slots:
    void actionsTapahtumat_slot(QString);
    void timeoutBankActions_slot();

private slots:
    void on_btnActionsNext_clicked();
    void on_btnActionsPrevious_clicked();
    void on_btnActionsClose_clicked();


private:
    Ui::BankActions *ui;

};

#endif // BANKACTIONS_H
