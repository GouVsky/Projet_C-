#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->dateBeginning->setDate(QDate::currentDate());
    ui->dateEnding->setDate(QDate::currentDate());

    utils = new CustomizedString(this);

    utils->forbidAlphaCaracteres(ui->customerIDSearch);
    utils->forbidNumericCaracteres(ui->customerNameSearch);
    utils->forbidNumericCaracteres(ui->customerFirstNameSearch);

    ui->customerView->setModel(model);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionQuit_triggered()
{
     close();
}

void MainWindow::on_actionAbout_triggered()
{
    About aboutDialog;

    aboutDialog.exec();
}

void MainWindow::on_actionAddingCustomer_triggered()
{
    CustomerController addingCustomerDialog;

    connect(&addingCustomerDialog, SIGNAL(addingSucceed(QString)), this, SLOT(showMessageStatusBar(QString)));

    addingCustomerDialog.exec();
}

void MainWindow::on_actionAddingEmployee_triggered()
{
    EmployeeController addingEmployeeDialog;

    connect(&addingEmployeeDialog, SIGNAL(addingSucceed(QString)), this, SLOT(showMessageStatusBar(QString)));

    addingEmployeeDialog.exec();
}

void MainWindow::on_searchCustomerSearchButton_clicked()
{
    // It is not necessary to verify if fields are full, because dates are always set.

    DataBaseCommunicator *db = DataBaseCommunicator::getInstance();

    model = db->searchCustomerFromDatabase(ui->customerIDSearch->text(), ui->customerNameSearch->text(), ui->customerFirstNameSearch->text(), ui->dateBeginning->date(), ui->dateEnding->date());

    ui->customerView->setModel(model);

    ui->customerView->horizontalHeader()->setStretchLastSection(true);
}

void MainWindow::on_searchCustomerEditButton_clicked()
{
    DataBaseCommunicator *dtbc = DataBaseCommunicator::getInstance();

    QItemSelectionModel *selectedRow = ui->customerView->selectionModel();

    if (selectedRow->model()->rowCount() > 0)
    {
        // We get index of the customer to edit.

        int indexCustomer = selectedRow->model()->index(selectedRow->selectedRows().at(0).row(), 0).data().toInt();

        Customer customer = dtbc->getCustomer(indexCustomer);

        CustomerController editCustomerDialog(&customer, indexCustomer);

        connect(&editCustomerDialog, SIGNAL(editingSucceed(QString)), this, SLOT(showMessageStatusBar(QString)));

        editCustomerDialog.exec();

        model->query().exec();
    }
}

void MainWindow::on_searchCustomerDeleteButton_clicked()
{
    DataBaseCommunicator *dtbc = DataBaseCommunicator::getInstance();

    QItemSelectionModel *selectedRow = ui->customerView->selectionModel();

    if (selectedRow->model()->rowCount() > 0)
    {
        // We get index of the customer to delete.

        int indexCustomer = selectedRow->model()->index(selectedRow->selectedRows().at(0).row(), 0).data().toInt();

        QMessageBox::StandardButton reply;

        reply = QMessageBox::question(this, "Warning", "Do you really want to delete this customer?",
                                      QMessageBox::Yes | QMessageBox::No);

        if (reply == QMessageBox::Yes)
        {
            dtbc->deleteCustomer(indexCustomer);

            showMessageStatusBar("You have deleted a customer.");

            model->query().exec();
         }
    }
}

void MainWindow::on_showEmployeesRefreshButton_clicked()
{
     DataBaseCommunicator *dtbc = DataBaseCommunicator::getInstance();
     dtbc->displayEmployeeList(ui->treeView);

}

void MainWindow::showMessageStatusBar(QString message)
{
    ui->statusBar->showMessage(message, 5000);
}

void MainWindow::on_customerNameSearch_textChanged(const QString &arg1)
{
    utils->capitalize(arg1, ui->customerNameSearch);
}

void MainWindow::on_customerFirstNameSearch_textChanged(const QString &arg1)
{
    utils->capitalize(arg1, ui->customerFirstNameSearch);
}
#include <iostream>
void MainWindow::on_showEmployeesEditButton_clicked()
{
     QItemSelectionModel *selectionModel= ui->treeView->selectionModel();
     //QVariant index = ui->treeView->currentIndex().data(Qt::UserRole);
      QVariant data = ui->treeView->currentIndex().data(Qt::UserRole);
     if(!data.isValid())
     {
         QMessageBox::information(this,"warning", "Please select an item to edit it");
     }
     else
     {
         //QVariant data= selectionModel->model()->data(index);
         int idEmployee = data.toInt();
         editemployee employeeEditDialog(idEmployee);
         employeeEditDialog.exec();
     }

}

void MainWindow::on_showEmployeesDeleteButton_clicked()
{
    QItemSelectionModel *selectionModel= ui->treeView->selectionModel();
    QModelIndex index = ui->treeView->currentIndex();
    if(!index.isValid())
    {
        QMessageBox::information(this,"warning", "Please select an item to edit it");
    }
    else
    {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Warning", "Do you really want to delete this employee?",
                                        QMessageBox::Yes|QMessageBox::No);
          if (reply == QMessageBox::Yes)
          {
            QVariant data= selectionModel->model()->data(index);
            QString text = data.toString();
            DataBaseCommunicator *dtbc =DataBaseCommunicator::getInstance();
            dtbc->deleteEmployee(text);
            dtbc->displayEmployeeList(ui->treeView);

            showMessageStatusBar("You have deleted an employee.");

          } else
          {

          }
    }


}
