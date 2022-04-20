#ifndef DRAWMONEY_H
#define DRAWMONEY_H

#include <QDialog>
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QJsonDocument>

namespace Ui {
class DrawMoney;
}

class DrawMoney : public QDialog
{
    Q_OBJECT

public:
    explicit DrawMoney(QWidget *parent = nullptr);
    ~DrawMoney();

private slots:
    void on_btnDraw20_clicked();
    void on_btnDraw40_clicked();
    void on_btnDraw60_clicked();
    void on_btnDraw100_clicked();
    void on_btnDraw200_clicked();
    void on_btnDraw500_clicked();
    void on_btnDrawClose_clicked();

private:
    Ui::DrawMoney *ui;
};

#endif // DRAWMONEY_H
