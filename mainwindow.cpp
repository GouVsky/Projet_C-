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
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionA_propos_triggered()
{
    aboutDialog= new About(this);
    aboutDialog->show();
}

void MainWindow::on_actionClient_triggered()
{
    addingCustomerDialog = new AddingCustomer(this);

    connect(addingCustomerDialog, SIGNAL(addingSucceed(QString)), this, SLOT(showMessageStatusBar(QString)));

    addingCustomerDialog->exec();
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

    ui->customerView->horizontalHeader()->setStretchLastSection(true);
}

void MainWindow::on_actionPersonnel_triggered()
{
    addingEmployeeDialog = new addingEmployee(this);

    connect(addingEmployeeDialog, SIGNAL(addingSucceed(QString)), this, SLOT(showMessageStatusBar(QString)));

    addingEmployeeDialog->exec();
}

void MainWindow::on_EditButton_clicked()
{
    editEmployeeDialog = new editemployee(this);
    editEmployeeDialog->exec();
}

void MainWindow::on_DeleteButton_clicked()
{

}

void MainWindow::showMessageStatusBar(QString message)
{
    ui->statusBar->showMessage(message, 5000);
}

void MainWindow::on_RefreshButon_clicked()
{
     DataBaseCommunicator *db = DataBaseCommunicator::getInstance();
     db->displayEmployeeList(ui->treeView);
}

void MainWindow::on_customerNameSearch_textChanged(const QString &arg1)
{
    utils->capitalize(arg1, ui->customerNameSearch);
}

void MainWindow::on_customerFirstNameSearch_textChanged(const QString &arg1)
{
    utils->capitalize(arg1, ui->customerFirstNameSearch);
}
