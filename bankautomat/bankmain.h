#ifndef BankMain_H
#define BankMain_H

#include "myurl.h"
#include "bankactions.h"
#include "drawmoney.h"

#include <QDialog>


namespace Ui {
class BankMain;
}

class BankMain : public QDialog
{
    Q_OBJECT

public:
    explicit BankMain(QString rfid, QByteArray token, QWidget *parent = nullptr);
    ~BankMain();

signals:
    void drawMoney_signal();
    void bankActions_signal();
    void logOut_signal();

public slots:
    void nimi_slot(QString);
    void saldo_slot(QString);
    void tapahtumat_slot(QString);
    void saldoUpdate_slot(QString);
    void timeoutBankMain_slot();

private slots:
    void on_buttonDrawMoney_clicked();
    void on_buttonActions_clicked();
    void on_buttonLogOut_clicked();

private:
    Ui::BankMain *ui;
};

#endif // BankMain_H
