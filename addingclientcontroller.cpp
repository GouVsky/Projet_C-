#include "addingclientcontroller.h"
#include "ui_addingclient.h"
#include "databasecommunicator.h"

AddingClient::AddingClient(QWidget *parent) : QDialog(parent), ui(new Ui::AddingClient)
{
    ui->setupUi(this);

    ui->editDate->setDate(QDate::currentDate());
    ui->editDate->setMinimumDate(QDate::currentDate());

    QRegExp regPhone("[0-9]{10}");
    phoneValidator = new QRegExpValidator(regPhone, this);
    ui->editPhoneNumber->setValidator(phoneValidator);

    QRegExp regPostalCode("[0-9]{5}");
    postalCodeValidator = new QRegExpValidator(regPostalCode, this);
    ui->editPostalCode->setValidator(postalCodeValidator);

    QRegExp withoutNumbers("[A-Za-z]+");
    stringWithoutNumbersValidator = new QRegExpValidator(withoutNumbers, this);
    ui->editName->setValidator(stringWithoutNumbersValidator);
    ui->editFirstName->setValidator(stringWithoutNumbersValidator);
    ui->editCity->setValidator(stringWithoutNumbersValidator);
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
        DataBaseCommunicator * dtbc= DataBaseCommunicator::getInstance();

        dtbc->addCustomerToDatabase(ui);

        accept();
    }
}

void AddingClient::capitalize(const QString &str, QLineEdit *lineEdit)
{
    int position = lineEdit->cursorPosition();

    QString text = str;

    text = text.toLower();

    text[0] = text[0].toUpper();

    lineEdit->setText(text);

    lineEdit->setCursorPosition(position);
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
