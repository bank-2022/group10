#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "login.h"
#include "pin.h"

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

private slots:
    void on_btnLogin_clicked();
    void serialReadyRead();


private:
    Ui::MainWindow *ui;
    Login *objectLogin;
    QSerialPort *mSerial;
    QString rfid;
    Pin *objectPin;
};
#endif // MAINWINDOW_H
