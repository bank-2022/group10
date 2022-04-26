#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "login.h"
#include "pin.h"
#include "banktimer.h"

#include <QMainWindow>
#include <QSerialPort>

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void timeoutHandler();

private slots:
    void on_btnLogin_clicked();
    void serialReadyRead();

signals:
   void timeStart_signal(states,events);


private:
    Ui::MainWindow *ui;
    Login *objectLogin;
    QSerialPort *mSerial;
    QString rfid;
    Pin *objectPin;
    bankTimer * pBanktimer;
};
#endif // MAINWINDOW_H
