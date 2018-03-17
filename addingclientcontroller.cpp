#include "addingclientcontroller.h"
#include "ui_addingclient.h"
#include "databasecommunicator.h"
#include "customer.h"

AddingClient::AddingClient(QWidget *parent) : AddingPerson(parent), ui(new Ui::AddingClient)
{
    ui->setupUi(this);

    ui->editDate->setDate(QDate::currentDate());
    ui->editDate->setMinimumDate(QDate::currentDate());

    forbidAlphaCaracteres(ui->editPhoneNumber, 10);
    forbidAlphaCaracteres(ui->editPostalCode, 5);

    forbidNumericCaracteres(ui->editName);
    forbidNumericCaracteres(ui->editFirstName);
    forbidNumericCaracteres(ui->editCity);
}

AddingClient::~AddingClient()
{
    delete ui;
}

bool AddingClient::checkRequiredInputs()
{
    bool requiredInputs = true;

    if (ui->editName->text().isEmpty() ||
        ui->editFirstName->text().isEmpty() ||
        ui->editAddress->text().isEmpty() ||
        ui->editPostalCode->text().isEmpty() ||
        ui->editCity->text().isEmpty())
    {
        requiredInputs = false;

        QMessageBox::warning(this, "Warning", "Some information is missing.");
    }

    return requiredInputs;
}

void AddingClient::on_cancel_clicked()
{
    close();
}

void AddingClient::on_add_clicked()
{
    if (checkRequiredInputs())
    {
        Customer client;
        client.setAddress(ui->editAddress->text());
        client.setCity(ui->editCity->text());
        client.setComments(ui->editComments->toPlainText());
        client.setConsultingDay(ui->editDate->dateTime());
        client.setDureeRDV(ui->editConsultingTime->text().toInt());
        client.setFirstName(ui->editFirstName->text());
        client.setName(ui->editName->text());
        client.setPhoneNumber(ui->editPhoneNumber->text().toInt());
        client.setPostalCode(ui->editPostalCode->text());
        client.setPriority(ui->priorityList->itemData(ui->priorityList->currentIndex()).toInt());

        DataBaseCommunicator * dtbc= DataBaseCommunicator::getInstance();

        dtbc->addCustomerToDatabase(&client);

        emit addingSucceed("New customer added to the database.");

        accept();
    }
}

void AddingClient::on_editName_textChanged(const QString &arg1)
{
    capitalize(arg1, ui->editName);
}

void AddingClient::on_editFirstName_textChanged(const QString &arg1)
{
    capitalize(arg1, ui->editFirstName);
}

void AddingClient::on_editCity_textChanged(const QString &arg1)
{
    capitalize(arg1, ui->editCity);
}
