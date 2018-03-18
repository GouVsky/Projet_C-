#include "customercontroller.h"
#include "ui_customer.h"

CustomerController::CustomerController(QWidget *parent) : QDialog(parent), ui(new Ui::CustomerController)
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

    DataBaseCommunicator * dtbc = DataBaseCommunicator::getInstance();

    ui->resourcesList->addItems(dtbc->getResourcesList());
}

CustomerController::~CustomerController()
{
    delete ui;
}

bool CustomerController::checkRequiredInputs()
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

void CustomerController::on_cancel_clicked()
{
    close();
}

void CustomerController::on_add_clicked()
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

void CustomerController::on_editName_textChanged(const QString &arg1)
{
    utils->capitalize(arg1, ui->editName);
}

void CustomerController::on_editFirstName_textChanged(const QString &arg1)
{
    utils->capitalize(arg1, ui->editFirstName);
}

void CustomerController::on_editCity_textChanged(const QString &arg1)
{
    utils->capitalize(arg1, ui->editCity);
}
