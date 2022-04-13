#ifndef LOGIN_H
#define LOGIN_H

#include "pin.h"

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


private:
    Ui::Login *ui;
    QString rfid;

    Pin *objectPin;


};

#endif // LOGIN_H
