#include "editemployee.h"
#include "ui_editemployee.h"

editemployee::editemployee(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::editemployee)
{
    ui->setupUi(this);
}

editemployee::editemployee(QString nomEmploye, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::editemployee)
{
    ui->setupUi(this);
    nomEmployee=nomEmploye;
    DataBaseCommunicator *dtbc = DataBaseCommunicator::getInstance();
    Resource * employeeFind = dtbc->fillChamps(nomEmployee);
    ui->NomInput->insert(nomEmployee);
    ui->PrenomInput->insert(employeeFind->getName());
    ui->comboBox->setCurrentText(employeeFind->getType()->getLabel());
    if (employeeFind->getType()->getLabel() == "Informaticien")
    {
        //dtbc->g
        //ui->editInformaticienLogin->insert();
    }
}

editemployee::~editemployee()
{
    delete ui;
}

void editemployee::enableOrDisableComputerScientistLayout(bool enabled)
{
    ui->informaticienIdentification->setEnabled(enabled);
    ui->InformaticienLogin->setEnabled(enabled);
    ui->editInformaticienLogin->setEnabled(enabled);
    ui->InformaticienPassword->setEnabled(enabled);
    ui->editInformaticienPassword->setEnabled(enabled);
}

void editemployee::on_comboBox_currentTextChanged(const QString &arg1)
{
    if (arg1 == "Informaticien")
    {
        enableOrDisableComputerScientistLayout(true);
    }

    else
    {
        enableOrDisableComputerScientistLayout(false);
    }
}
void editemployee::on_editemployee_accepted()
{
    DataBaseCommunicator *dtbc = DataBaseCommunicator::getInstance();
    //dtbc->fillChamps(nomEmployee);
}
