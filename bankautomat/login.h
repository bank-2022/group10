#ifndef LOGIN_H
#define LOGIN_H


#include <QDialog>
#include <QString>


namespace Ui {
class Login;
}

class Login : public QDialog
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();

public slots:



private slots:
    void on_btnLoginLogin_clicked();

signals:
    void login_signal();
    void korttinumero_signal(QString);
    void loggingIn_signal();


private:
    Ui::Login *ui;
    QString rfid;
};

#endif // LOGIN_H
