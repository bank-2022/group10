#include "drawanothersum.h"
#include "ui_drawanothersum.h"

DrawAnotherSum::DrawAnotherSum(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DrawAnotherSum)
{
    ui->setupUi(this);
    connect(ui->lineEditAmount, SIGNAL(textChanged(QString)),
            this, SLOT(on_pushButtonOK_clicked()));
    on_pushButtonOK_clicked();

}

DrawAnotherSum::~DrawAnotherSum()
{
    delete ui;
}

void DrawAnotherSum::setSum(const QString &sum)
{
    ui->lineEditAmount->setText(sum);
}

QString DrawAnotherSum::sum() const
{
    return ui->lineEditAmount->text();
}


void DrawAnotherSum::on_pushButtonOK_clicked()
{
   ui->pushButtonOK->setEnabled(!ui->lineEditAmount->text().isEmpty());

}


