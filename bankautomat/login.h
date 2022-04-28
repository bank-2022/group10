#ifndef LOGIN_H
#define LOGIN_H

#include "pin.h"
#include "banktimer.h"
#include <QDialog>


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

signals:
    void timeReset_signal(states,events);


private:
    Ui::Login *ui;
    QString rfid;


    Pin *objectPin;
    bankTimer * pBankTimer;


};

#endif // LOGIN_H
