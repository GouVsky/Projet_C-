#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

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

    connect(addingClientDialog, SIGNAL(addingSucceed(QString)), this, SLOT(showMessageStatusBar(QString)));

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

void MainWindow::showMessageStatusBar(QString message)
{
    ui->statusBar->showMessage(message, 5000);
}

void MainWindow::on_RefreshButon_clicked()
{
     DataBaseCommunicator *db = DataBaseCommunicator::getInstance();
     db->displayEmployeeList(ui->treeView);
}
