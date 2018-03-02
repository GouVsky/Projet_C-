#include "searchclientcontroller.h"

searchClientController::searchClientController(QObject *parent) : QObject(parent)
{
}

void searchClientController::checkOneFieldFullAtLeast(Ui::MainWindow * ui)
{
    bool oneFieldIsFull = true;

    if (ui->customerIDSearch->text().isEmpty() &&
        ui->customerNameSearch->text().isEmpty() &&
        ui->customerFirstNameSearch->text().isEmpty())
    {
        oneFieldIsFull = false;
    }
}
