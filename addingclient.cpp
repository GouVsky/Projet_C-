#include "addingclient.h"
#include "ui_addingclient.h"

AddingClient::AddingClient(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddingClient)
{
    ui->setupUi(this);
}

AddingClient::~AddingClient()
{
    delete ui;
}

void AddingClient::on_cancel_clicked()
{
    close();
}

void AddingClient::on_add_clicked()
{

}
