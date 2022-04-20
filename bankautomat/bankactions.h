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
    explicit BankActions(QWidget *parent = nullptr);
    ~BankActions();

private slots:
    void on_btnActionsNext_clicked();
    void on_btnActionsPrevious_clicked();
    void on_btnActionsClose_clicked();
    void on_listView_indexesMoved(const QModelIndexList &indexes);

private:
    Ui::BankActions *ui;
    MyUrl *objectMyUrl;

};

#endif // BANKACTIONS_H
