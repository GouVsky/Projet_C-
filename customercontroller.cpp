#include "customercontroller.h"
#include "ui_customer.h"

CustomerController::CustomerController(QWidget *parent) : QDialog(parent), ui(new Ui::CustomerController)
{
    ui->setupUi(this);

    ui->editDate->setDate(QDate::currentDate());
    ui->editDate->setMinimumDate(QDate::currentDate());
    ui->editDate->setMaximumDate(QDate::currentDate().addDays(30));

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

    for (int i = 0; i < customer->getResourcesNumber(); i++)
    {
        QString id = "[" + QString::number(customer->getResource(i).getId()) + "]";

        ui->resourcesList->findItems(id ,Qt::MatchContains)[0]->setSelected(true);
    }

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

void CustomerController::setCustomerFields()
{
    DataBaseCommunicator * dtbc = DataBaseCommunicator::getInstance();

    customer->setAddress(ui->editAddress->text());
    customer->setCity(ui->editCity->text());
    customer->setComments(ui->editComments->toPlainText() + "\n" + ui->remarquesEdit->toPlainText());
    customer->setConsultingDay(ui->editDate->date());
    customer->setDureeRDV(ui->editConsultingTime->value());
    customer->setFirstName(ui->editFirstName->text());
    customer->setName(ui->editName->text());
    customer->setPhoneNumber(ui->editPhoneNumber->text().toInt());
    customer->setPostalCode(ui->editPostalCode->text());
    customer->setPriority(ui->priorityList->value());

    int selectedItemsNumber = ui->resourcesList->selectedItems().size();

    for (int i = 0; i < selectedItemsNumber; i++)
    {
        // We get the number part of the string.
        // We begin at 1 to jump the '[' character.
        // We have extracted all the number when we reach the ']' character.

        int count = 1;

        QString id;
        QString resourceString = ui->resourcesList->selectedItems()[i]->text();

        while (resourceString[count] != ']')
        {
            id += resourceString[count];

            count++;
        }

        Resource * resource = dtbc->findEmployee(id.toInt());

        customer->setResource(*resource);
    }
}

void CustomerController::on_add_clicked()
{
    if (checkRequiredInputs())
    {
        DataBaseCommunicator * dtbc = DataBaseCommunicator::getInstance();

        setCustomerFields();

        dtbc->addCustomer(customer);

        emit addingSucceed("New customer added to the database.");

        accept();
    }
}

void CustomerController::on_edit_clicked()
{
    if (checkRequiredInputs())
    {
        DataBaseCommunicator * dtbc = DataBaseCommunicator::getInstance();

        // We delete all Rendez-vous of the customer.

        dtbc->deleteRdv(customer->getId());

        setCustomerFields();

        dtbc->addCustomer(customer, true);

        emit editingSucceed("Customer edited.");

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
