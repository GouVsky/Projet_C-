#include "addingclientcontroller.h"
#include "ui_addingclient.h"

AddingClient::AddingClient(QWidget *parent) : QDialog(parent), ui(new Ui::AddingClient)
{
    ui->setupUi(this);

    QRegExp regPhone("[0-9]{10}");
    phoneValidator = new QRegExpValidator(regPhone, this);
    ui->editPhoneNumber->setValidator(phoneValidator);

    QRegExp regPostalCode("[0-9]{5}");
    postalCodeValidator = new QRegExpValidator(regPostalCode, this);
    ui->editPostalCode->setValidator(postalCodeValidator);
}

AddingClient::~AddingClient()
{
    delete ui;
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

void AddingClient::on_cancel_clicked()
{
    close();
}

void AddingClient::on_add_clicked()
{

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
