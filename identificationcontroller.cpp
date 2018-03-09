#include "identificationcontroller.h"
#include "ui_identification.h"

#include "databasecommunicator.h"

Identification::Identification(QWidget *parent) : QDialog(parent), ui(new Ui::Identification)
{
    ui->setupUi(this);
}

Identification::~Identification()
{
    delete ui;
}

bool Identification::checkIdentification()
{
    bool check = true;

    DataBaseCommunicator *dbc = DataBaseCommunicator::getInstance();

    if (!dbc->checkLoginPassword(ui->loginField->text(), ui->passwordField->text()))
    {
        check = false;

        QMessageBox::warning(this, "Warning !", "Incorrect login or password !");

        ui->passwordField->clear();
    }

    return check;
}

void Identification::on_cancel_clicked()
{
    close();
}

void Identification::on_connect_clicked()
{
    if (checkIdentification())
    {
        accept();
    }
}
