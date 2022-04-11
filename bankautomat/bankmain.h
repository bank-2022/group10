#ifndef BANKMAIN_H
#define BANKMAIN_H

#include <QDialog>
#include <QDebug>

namespace Ui {
class BankMain;
}

class BankMain : public QDialog
{
    Q_OBJECT

public:
    explicit BankMain(QWidget *parent = nullptr);
    ~BankMain();

private:
    Ui::BankMain *ui;
};

#endif // BANKMAIN_H
