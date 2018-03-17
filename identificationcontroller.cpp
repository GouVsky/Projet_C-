#include "identificationcontroller.h"
#include "ui_identification.h"

Identification::Identification(MainWindow *mainWindow, QWidget *parent) : QDialog(parent), ui(new Ui::Identification)
{
    ui->setupUi(this);

    connect(this, SIGNAL(connectionSucceed(QString)), mainWindow, SLOT(showMessageStatusBar(QString)));
}

Identification::~Identification()
{
    delete ui;
}

bool Identification::checkIdentification()
{
    bool check = true;

    DataBaseCommunicator *dbc = DataBaseCommunicator::getInstance();

    if (dbc->checkLoginPassword(ui->loginField->text(), ui->passwordField->text()))
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

        emit connectionSucceed("Connected to the application.");
    }
}

