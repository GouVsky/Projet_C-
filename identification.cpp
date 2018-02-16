#include "identification.h"
#include "ui_identification.h"

Identification::Identification(QWidget *parent) : QDialog(parent), ui(new Ui::Identification)
{
    ui->setupUi(this);

    // We center the window.

    const QRect screen = QApplication::desktop()->screenGeometry();

    this->move(screen.center() - this->rect().center());
}




Identification::~Identification()
{
    delete ui;
}




void Identification::on_cancel_clicked()
{
    close();
}




void Identification::on_connect_clicked()
{

}
