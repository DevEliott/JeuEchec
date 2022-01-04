#include "ui_MenuDemarrer.h"
#include "MenuDemarrer.hpp"


vue::MenuDemarrer::MenuDemarrer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MenuDemarrer)
{
    ui->setupUi(this);
}

vue::MenuDemarrer::~MenuDemarrer()
{
    delete ui;
}

void vue::MenuDemarrer::on_pushButton_Valider_clicked()
{
    emit boutonValiderAppuye();
}
