#include "DialogPat.hpp"
#include "ui_DialogPat.h"

vue::DialogPat::DialogPat(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogPat)
{
    ui->setupUi(this);
}

vue::DialogPat::~DialogPat()
{
    delete ui;
}


void vue::DialogPat::recevoirPatMainWindow(bool couleur)
{
    if (couleur == true)
        ui->label->setText(QString("<html><head/><body><p align=\"center\"><span style=\" font-size:16pt; font-weight:600;\">Pat des Blancs</span></p></body></html>"));

    else
        ui->label->setText(QString("<html><head/><body><p align=\"center\"><span style=\" font-size:16pt; font-weight:600;\">Pat des Noirs</span></p></body></html>"));
}


void vue::DialogPat::on_pushButton_clicked()
{
    emit boutonValiderAppuye();
}
