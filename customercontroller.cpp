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

    ui->resourcesList->addItems(dtbc->getResourcesTypesList());

    ui->edit->setVisible(false);
    ui->add->setVisible(true);

    customer = new Customer();
}

CustomerController::CustomerController(Customer *customer, int id, QWidget *parent) : QDialog(parent), ui(new Ui::CustomerController)
{
    ui->setupUi(this);

    ui->editName->setText(customer->getName());
    ui->editFirstName->setText(customer->getFirstName());
    ui->editAddress->setText(customer->getAddress());
    ui->editPostalCode->setText(customer->getPostalCode());
    ui->editCity->setText(customer->getCity());
    ui->editComments->setText(customer->getComments());
    ui->editDate->setDate(customer->getConsultingDay());
    ui->editConsultingTime->setValue(customer->getDureeRDV());
    ui->editPhoneNumber->setText(QString::number(customer->getPhoneNumber()));
    ui->priorityList->setValue(customer->getPriority());

    DataBaseCommunicator * dtbc = DataBaseCommunicator::getInstance();

    ui->resourcesList->addItems(dtbc->getResourcesTypesList());

    // We substract 1 because Id of Tables begin at 1 and Id of QCombobox begin at 0.
    ui->resourcesList->setCurrentIndex(customer->getResource()->getType()->getId() - 1);

    ui->edit->setVisible(true);
    ui->add->setVisible(false);

    this->customer = new Customer();
    this->customer->setId(id);
}

CustomerController::~CustomerController()
{
    delete ui;
    delete customer;
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
        customer->setAddress(ui->editAddress->text());
        customer->setCity(ui->editCity->text());
        customer->setComments(ui->editComments->toPlainText());
        customer->setConsultingDay(ui->editDate->date());
        customer->setDureeRDV(ui->editConsultingTime->value());
        customer->setFirstName(ui->editFirstName->text());
        customer->setName(ui->editName->text());
        customer->setPhoneNumber(ui->editPhoneNumber->text().toInt());
        customer->setPostalCode(ui->editPostalCode->text());
        customer->setPriority(ui->priorityList->value());

        DataBaseCommunicator * dtbc = DataBaseCommunicator::getInstance();

        Resource resource = dtbc->findEmployee(ui->resourcesList->currentText()[1].digitValue());

        customer->setResource(&resource);

        dtbc->addCustomerToDatabase(customer, customer->getResource()->getType()->getId());

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

void CustomerController::on_edit_clicked()
{
    if (checkRequiredInputs())
    {
        customer->setAddress(ui->editAddress->text());
        customer->setCity(ui->editCity->text());
        customer->setComments(ui->editComments->toPlainText());
        customer->setConsultingDay(ui->editDate->date());
        customer->setDureeRDV(ui->editConsultingTime->text().toInt());
        customer->setFirstName(ui->editFirstName->text());
        customer->setName(ui->editName->text());
        customer->setPhoneNumber(ui->editPhoneNumber->text().toInt());
        customer->setPostalCode(ui->editPostalCode->text());
        customer->setPriority(ui->priorityList->value());

        DataBaseCommunicator * dtbc = DataBaseCommunicator::getInstance();

        Resource resource = dtbc->findEmployee(ui->resourcesList->currentText()[1].digitValue());

        // We get the id of the resource.
        customer->setResource(&resource);

        dtbc->updateCustomer(customer);

        emit editingSucceed("Customer edited.");

        accept();
    }
}
