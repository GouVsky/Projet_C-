#include "editemployee.h"
#include "ui_editemployee.h"

editemployee::editemployee(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::editemployee)
{
    ui->setupUi(this);
}

editemployee::editemployee(QString nomEmploye, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::editemployee)
{
    ui->setupUi(this);
    nomEmployee=nomEmploye;
}

editemployee::~editemployee()
{
    delete ui;
}

void editemployee::on_editemployee_accepted()
{
    DataBaseCommunicator *dtbc = DataBaseCommunicator::getInstance();
    dtbc->fillChamps(nomEmployee);

}
