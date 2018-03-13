#include "editemployee.h"
#include "ui_editemployee.h"

editemployee::editemployee(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::editemployee)
{
    ui->setupUi(this);
}

editemployee::~editemployee()
{
    delete ui;
}
