#include "adddivers.h"
#include "ui_adddivers.h"

AddDivers::AddDivers(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddDivers)
{
    ui->setupUi(this);
}

AddDivers::~AddDivers()
{
    delete ui;
}

void AddDivers::on_OK_buton_clicked()
{
    Resource DiversRessource;
    Type TypeDivers;
    DiversRessource.setName(ui->NomInput->text());
    DiversRessource.setFirstName(ui->PrenomInput->text());
    TypeDivers.setLabel("Divers");
    DiversRessource.setType(TypeDivers);
    DataBaseCommunicator *dtbc = DataBaseCommunicator::getInstance();
    dtbc->insertDivers(DiversRessource);
    this->accept();

}

void AddDivers::on_Cancel_Buton_clicked()
{
    this->close();
}
