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
    aPropoDialog= new apropos(this);
    aPropoDialog->show();
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
