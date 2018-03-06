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

void addingEmployee::enableOrDisableComputerScientistLayout(bool enabled)
{
    ui->informaticienIdentification->setEnabled(enabled);
    ui->InformaticienLogin->setEnabled(enabled);
    ui->editInformaticienLogin->setEnabled(enabled);
    ui->InformaticienPassword->setEnabled(enabled);
    ui->editInformaticienPassword->setEnabled(enabled);
}

void addingEmployee::on_comboBox_currentIndexChanged(int index)
{
    // Index 0 refers to the type "Informaticien".

    if (index == 0)
    {
        enableOrDisableComputerScientistLayout(true);
    }

    else
    {
        enableOrDisableComputerScientistLayout(false);
    }
}
