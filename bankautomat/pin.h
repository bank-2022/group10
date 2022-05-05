#ifndef PIN_H
#define PIN_H

#include <QDialog>
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


signals:
    void pinBtnPress_signal();
    void pinCancel_signal();
    void pinOk_signal();
    void pin_signal(QString);

public slots:
    void cardLocked_slot();
    void loginSuccess_slot();
    void wrongPin_slot();
    void attemptsLeft_slot(int);
    void timeoutPin_slot();

private slots:
    void on_pushButton_Cancel_clicked();
    void on_pushButton_Clear_clicked();
    void on_pushButton_OK_clicked();
    void NumPressed();



private:
    Ui::Pin *ui;
    QString rfid;
    QString pin;


};

#endif // PIN_H
