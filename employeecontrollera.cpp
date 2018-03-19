#include "employeecontrollera.h"
#include "ui_employee.h"

EmployeeController::EmployeeController(QWidget *parent) : QDialog(parent), ui(new Ui::EmployeeController)
{
    ui->setupUi(this);

    utils = new CustomizedString(this);

    utils->forbidNumericCaracteres(ui->NomInput);
    utils->forbidNumericCaracteres(ui->PrenomInput);

    enableOrDisableComputerScientistLayout(false);

    // We get resources list from the database.
    // It will be not necessary to add resource in combobox if it is added in the database.

    DataBaseCommunicator * dtbc = DataBaseCommunicator::getInstance();

    ui->comboBox->addItems(dtbc->getResourcesList());
}

EmployeeController::~EmployeeController()
{
    delete ui;
}

void EmployeeController::on_QuitButton_clicked()
{
    close();
}

void EmployeeController::enableOrDisableComputerScientistLayout(bool enabled)
{
    ui->informaticienIdentification->setEnabled(enabled);
    ui->InformaticienLogin->setEnabled(enabled);
    ui->editInformaticienLogin->setEnabled(enabled);
    ui->InformaticienPassword->setEnabled(enabled);
    ui->editInformaticienPassword->setEnabled(enabled);
}

void EmployeeController::on_comboBox_currentTextChanged(const QString &arg1)
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


void EmployeeController::on_NomInput_textChanged(const QString &arg1)
{
    utils->capitalize(arg1, ui->NomInput);
}

void EmployeeController::on_PrenomInput_textChanged(const QString &arg1)
{
    utils->capitalize(arg1, ui->PrenomInput);
}

void EmployeeController::on_AddButton_clicked()
{
    Type type;
    Account account;
    Resource resource;

    DataBaseCommunicator * dtbc = DataBaseCommunicator::getInstance();

    // We add 1 because the index of the combobox starts at 0.
    // And the first id in the database is 1.

    type.setId(ui->comboBox->currentIndex() + 1);
    type.setLabel(ui->comboBox->itemData(ui->comboBox->currentIndex()).toString());

    resource.setName(ui->NomInput->text());
    resource.setFirstName(ui->PrenomInput->text());
    resource.setType(&type);

    int index = dtbc->addResourceToDatabase(&resource);

    if (type.getLabel() == "Informaticien")
    {
        account.setLogin(ui->editInformaticienLogin->text());
        account.setPassword(ui->editInformaticienPassword->text());

        dtbc->addAccountToDatabase(&account, index);
    }

    emit addingSucceed("New resource added to the database.");

    accept();
}
