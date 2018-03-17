#include "addingcustomercontroller.h"
#include "ui_addingcustomer.h"

AddingCustomer::AddingCustomer(QWidget *parent) : QDialog(parent), ui(new Ui::AddingCustomer)
{
    ui->setupUi(this);

    ui->editDate->setDate(QDate::currentDate());
    ui->editDate->setMinimumDate(QDate::currentDate());

    utils = new CustomizedString(this);

    utils->forbidAlphaCaracteres(ui->editPhoneNumber, 10);
    utils->forbidAlphaCaracteres(ui->editPostalCode, 5);

    utils->forbidNumericCaracteres(ui->editName);
    utils->forbidNumericCaracteres(ui->editFirstName);
    utils->forbidNumericCaracteres(ui->editCity);
}

AddingCustomer::~AddingCustomer()
{
    delete ui;
}

bool AddingCustomer::checkRequiredInputs()
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

void AddingCustomer::on_cancel_clicked()
{
    close();
}

void AddingCustomer::on_add_clicked()
{
    if (checkRequiredInputs())
    {
        Customer customer;
        customer.setAddress(ui->editAddress->text());
        customer.setCity(ui->editCity->text());
        customer.setComments(ui->editComments->toPlainText());
        customer.setConsultingDay(ui->editDate->dateTime());
        customer.setDureeRDV(ui->editConsultingTime->text().toInt());
        customer.setFirstName(ui->editFirstName->text());
        customer.setName(ui->editName->text());
        customer.setPhoneNumber(ui->editPhoneNumber->text().toInt());
        customer.setPostalCode(ui->editPostalCode->text());
        customer.setPriority(ui->priorityList->itemData(ui->priorityList->currentIndex()).toInt());

        DataBaseCommunicator * dtbc = DataBaseCommunicator::getInstance();

        dtbc->addCustomerToDatabase(&customer);

        emit addingSucceed("New customer added to the database.");

        accept();
    }
}

void AddingCustomer::on_editName_textChanged(const QString &arg1)
{
    utils->capitalize(arg1, ui->editName);
}

void AddingCustomer::on_editFirstName_textChanged(const QString &arg1)
{
    utils->capitalize(arg1, ui->editFirstName);
}

void AddingCustomer::on_editCity_textChanged(const QString &arg1)
{
    utils->capitalize(arg1, ui->editCity);
}
