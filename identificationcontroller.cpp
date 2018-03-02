#include "identificationcontroller.h"
#include "ui_identification.h"

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
    // The variable 'check' is initialized to 'false' to test the QMessageBox.

    bool check = true;

    if (!check)
    {
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
