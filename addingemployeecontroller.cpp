#include "addingemployeecontroller.h"
#include "ui_addingemployee.h"

addingEmployee::addingEmployee(QWidget *parent) : AddingPerson(parent), ui(new Ui::addingEmployee)
{
    ui->setupUi(this);

    forbidNumericCaracteres(ui->NomInput);
    forbidNumericCaracteres(ui->PrenomInput);
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

void addingEmployee::on_NomInput_textChanged(const QString &arg1)
{
    capitalize(arg1, ui->NomInput);
}

void addingEmployee::on_PrenomInput_textChanged(const QString &arg1)
{
    capitalize(arg1, ui->PrenomInput);
}
