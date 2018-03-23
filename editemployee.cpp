#include "editemployee.h"
#include "ui_editemployee.h"

editemployee::editemployee(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::editemployee)
{
    ui->setupUi(this);
}

editemployee::editemployee(int idEmploye, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::editemployee)
{
    ui->setupUi(this);
    idEmployee=idEmploye;
    DataBaseCommunicator *dtbc = DataBaseCommunicator::getInstance();
    Resource * employeeFind = dtbc->findEmployee(idEmployee);
    int index= ui->comboBox->findText(employeeFind->getType()->getLabel());
    ui->NomInput->insert(employeeFind->getFirstName());
    ui->PrenomInput->insert(employeeFind->getName());
    ui->comboBox->setCurrentIndex( index);
    if (employeeFind->getType()->getLabel() == "Informaticien")
    {
        Account * infoAccount = dtbc->getAccount(idEmployee);
        ui->editInformaticienLogin->insert(infoAccount->getLogin());
        ui->editInformaticienPassword->insert(infoAccount->getPassword());
    }
}

editemployee::~editemployee()
{
    delete ui;
}

bool editemployee::checkRequiredInputs()
{
    bool requiredInputs = true;

    // Check if fields are correctly fill.
    // If the resource is a computer scientist, we check if the login and the password are filled out.

    if (ui->NomInput->text().isEmpty() ||
        ui->PrenomInput->text().isEmpty() ||
        (ui->comboBox->currentText() == "Informaticien" &&
         (ui->editInformaticienLogin->text().isEmpty() ||
          ui->editInformaticienPassword->text().isEmpty())))
    {
        requiredInputs = false;

        QMessageBox::warning(this, "Warning", "Some information is missing.");
    }

    return requiredInputs;
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

void editemployee::on_Buton_cancel_clicked()
{
    this->close();
}

void editemployee::on_Edit_buton_clicked()
{
    DataBaseCommunicator *dtbc = DataBaseCommunicator::getInstance();
    Resource employeeToSend;
    Type typeEmployee;
    Account acountToUpdate;

    typeEmployee.setLabel(ui->comboBox->currentText());
    employeeToSend.setName(ui->NomInput->text());
    employeeToSend.setFirstName(ui->PrenomInput->text());
    employeeToSend.setType(typeEmployee);
    dtbc->editEmployee(employeeToSend, idEmployee);

    if (typeEmployee.getLabel() == "Informaticien")
    {
        acountToUpdate.setLogin(ui->editInformaticienLogin->text());
        acountToUpdate.setPassword(ui->editInformaticienPassword->text());
        dtbc->updateAccount(&acountToUpdate, idEmployee);
    }
    this->close();
}
