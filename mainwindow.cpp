#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "apropos.h"

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
