#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    identificationDialog = new Identification(this);

    ui->dateBeginning->setDate(QDate::currentDate());
    ui->dateEnding->setDate(QDate::currentDate());
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

void MainWindow::on_searchCustomerButton_clicked()
{
    // It is not necessary to verify if fields are full, because dates are always set.

    DataBaseCommunicator *db = DataBaseCommunicator::getInstance();

    QSqlQueryModel *model = db->searchCustomerFromDatabase(ui->customerIDSearch->text(), ui->customerNameSearch->text(), ui->customerFirstNameSearch->text(), ui->dateBeginning->date(), ui->dateEnding->date());

    ui->customerView->setModel(model);
}

void MainWindow::on_actionPersonnel_triggered()
{
    addingEmployeeDialog = new addingEmployee(this);
    addingEmployeeDialog->exec();
}

void MainWindow::on_EditButton_clicked()
{
    EditEmployeeDialog = new editemployee(this);
    EditEmployeeDialog->exec();
}

void MainWindow::on_DeleteButton_clicked()
{

}

