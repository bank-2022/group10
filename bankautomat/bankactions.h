#ifndef BANKACTIONS_H
#define BANKACTIONS_H

#include <QDialog>

namespace Ui {
class BankActions;
}

class BankActions : public QDialog
{
    Q_OBJECT

public:
    explicit BankActions(QWidget *parent = nullptr);
    ~BankActions();

private:
    Ui::BankActions *ui;
};

#endif // BANKACTIONS_H
