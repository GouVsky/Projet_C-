#include "searchcustomercontroller.h"

SearchCustomerController::SearchCustomerController(QObject *parent) : QObject(parent)
{

}

bool SearchCustomerController::checkOneFieldSearchCustomerFullAtLeast(Ui::MainWindow * ui)
{
    bool oneFieldIsFull = true;

    if (ui->customerIDSearch->text().isEmpty() &&
        ui->customerNameSearch->text().isEmpty() &&
        ui->customerFirstNameSearch->text().isEmpty())
    {
        oneFieldIsFull = false;
    }

    return oneFieldIsFull;
}
