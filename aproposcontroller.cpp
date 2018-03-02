#include "aproposcontroller.h"
#include "ui_apropos.h"

apropos::apropos(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::apropos)
{
    ui->setupUi(this);
}

apropos::~apropos()
{
    delete ui;
}

void apropos::on_pushButton_clicked()
{
    close() ;
}
