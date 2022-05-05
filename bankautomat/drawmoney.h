#ifndef DRAWMONEY_H
#define DRAWMONEY_H

#include <QDialog>


namespace Ui {
class DrawMoney;
}

class DrawMoney : public QDialog
{
    Q_OBJECT

public:
    explicit DrawMoney(QString id_kortti, QString id_tili, QByteArray token, QWidget *parent = nullptr);
    ~DrawMoney();

signals:
    void updateSignal();
    void btnDrawX_signal();
    void button_signal(float);
    void moneyBtnPressed_signal();
    void moneyBtnClose_signal();

public slots:
    void drawSuccess_slot();
    void drawFailure_slot();
    void timeoutDrawMoney_slot();

private slots:

    void buttonClicked();
    void on_btnDrawClose_clicked();
    void on_btnDrawX_clicked();

private:
    Ui::DrawMoney *ui;
    QVector <QPushButton *> buttons;
    int sum;
};

#endif // DRAWMONEY_H
