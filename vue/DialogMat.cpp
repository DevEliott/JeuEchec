#include "DialogMat.hpp"
#include "ui_DialogMat.h"



vue::DialogMat::DialogMat(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogMat)
{
    ui->setupUi(this);
}

vue::DialogMat::~DialogMat()
{
    delete ui;
}

void vue::DialogMat::recevoirMatMainWindow(bool couleur)
{
    if (couleur == true)
        ui->label->setText(QString("<html><head/><body><p align=\"center\"><span style=\" font-size:16pt; font-weight:600;\">Echec et mat des Blancs</span></p></body></html>"));

    else
        ui->label->setText(QString("<html><head/><body><p align=\"center\"><span style=\" font-size:16pt; font-weight:600;\">Echec et mat des Noirs</span></p></body></html>"));
}

void vue::DialogMat::on_pushButton_clicked()
{

    emit boutonValiderAppuye();
}
