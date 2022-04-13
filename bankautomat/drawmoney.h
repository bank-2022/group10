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
    explicit DrawMoney(QWidget *parent = nullptr);
    ~DrawMoney();

private:
    Ui::DrawMoney *ui;
};

#endif // DRAWMONEY_H
