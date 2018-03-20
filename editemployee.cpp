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
    Resource * employeeFind = dtbc->findEmployee(nomEmployee);
    int index= ui->comboBox->findText(employeeFind->getType()->getLabel());
    ui->NomInput->insert(nomEmployee);
    ui->PrenomInput->insert(employeeFind->getName());
    ui->comboBox->setCurrentIndex( index);
    if (employeeFind->getType()->getLabel() == "Informaticien")
    {
        Account * infoAccount = dtbc->getAccount(nomEmployee);
        ui->editInformaticienLogin->insert(infoAccount->getLogin());
        ui->editInformaticienPassword->insert(infoAccount->getPassword());
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
    Resource * employeeFind = dtbc->findEmployee(nomEmployee);
    Resource * employeeToSend = new Resource();
    Type * typeEmployee = new Type();
    employeeToSend->setName(ui->NomInput->text());
    employeeToSend->setFirstName(ui->PrenomInput->text());
    employeeToSend->setType(typeEmployee);
    typeEmployee->setLabel(ui->comboBox->currentText());

}

void editemployee::on_Buton_cancel_clicked()
{
    this->close();
}
