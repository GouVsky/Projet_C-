#include "addingemployee.h"
#include "ui_addingemployee.h"

addingEmployee::addingEmployee(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addingEmployee)
{
    ui->setupUi(this);
}

addingEmployee::~addingEmployee()
{
    delete ui;
}

void addingEmployee::on_QuitButton_clicked()
{
    close();
}
