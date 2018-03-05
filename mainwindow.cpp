#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    identificationDialog = new Identification(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionA_propos_triggered()
{
    aProposDialog= new apropos(this);
    aProposDialog->show();
}

void MainWindow::on_actionClient_triggered()
{
    addingClientDialog = new AddingClient(this);
    addingClientDialog->exec();
}

void MainWindow::on_actionQuitter_triggered()
{
    close();
}

bool MainWindow::checkOneFieldSearchCustomerFullAtLeast()
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

void MainWindow::on_searchCustomerButton_clicked()
{
    if (checkOneFieldSearchCustomerFullAtLeast())
    {

    }
}

void MainWindow::on_actionPersonnel_triggered()
{
    addingEmployeeDialog = new addingEmployee(this);
    addingEmployeeDialog->show();
}
