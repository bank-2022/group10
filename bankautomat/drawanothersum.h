#ifndef DRAWANOTHERSUM_H
#define DRAWANOTHERSUM_H

#include <QDialog>

namespace Ui {
class DrawAnotherSum;
}

class DrawAnotherSum : public QDialog
{
    Q_OBJECT

public:
    explicit DrawAnotherSum(QWidget *parent = nullptr);
    ~DrawAnotherSum();
    void setSum(const QString &sum);
    QString sum() const;

private slots:
    void on_pushButtonOK_clicked();

private:
    Ui::DrawAnotherSum *ui;
};

#endif // DRAWANOTHERSUM_H
