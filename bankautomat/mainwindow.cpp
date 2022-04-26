#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    pBanktimer = new bankTimer;
    objectLogin = new Login;
    mSerial = new QSerialPort(this);

    if (mSerial->isOpen()) {
        qDebug() << "Serial already connected, disconnecting!";
        mSerial->close();
    }

    mSerial->setPortName("com4");
    mSerial->setBaudRate(QSerialPort::Baud115200);
    mSerial->setDataBits(QSerialPort::Data8);
    mSerial->setParity(QSerialPort::NoParity);
    mSerial->setStopBits(QSerialPort::OneStop);
    mSerial->setFlowControl(QSerialPort::NoFlowControl);

    if(mSerial->open(QIODevice::ReadWrite)) {
        qDebug() << "SERIAL: OK!";
    } else {
        qDebug() << "SERIAL: ERROR!";
    }

    connect(mSerial, &QSerialPort::readyRead,
            this, &MainWindow::serialReadyRead);


    connect(pBanktimer,SIGNAL(timeout_signal()),
                this,SLOT(timeoutHandler()));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete objectLogin;
    delete objectPin;
    ui=nullptr;
    objectLogin=nullptr;
    objectPin=nullptr;
    disconnect(pBanktimer,SIGNAL(timeout_signal()),
                this,SLOT(timeoutHandler()));
}


void MainWindow::on_btnLogin_clicked()
{
objectLogin->show();

connect(this,SIGNAL(timeStart_signal(states,events)),
        pBanktimer,SLOT(runStateMachine(states,events)));
emit timeStart_signal(tier0,timeStart);
disconnect(this,SIGNAL(timeStart_signal(states,events)),
        pBanktimer,SLOT(runStateMachine(states,events)));
}

void MainWindow::serialReadyRead()
{
    QString data = mSerial->readAll();
    rfid = data;
    rfid.remove(0,3);
    rfid.chop(3);
    qDebug() << rfid;
    objectPin = new Pin(rfid);
    objectPin->show();
}

void MainWindow::timeoutHandler()
{
    objectLogin->close();
}

