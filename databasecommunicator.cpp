#include "databasecommunicator.h"

DataBaseCommunicator *DataBaseCommunicator::instance = nullptr;


DataBaseCommunicator::DataBaseCommunicator(QObject *parent) : QObject(parent)
{
    db = QSqlDatabase::database("QSQLITE");

    db.open();
}

DataBaseCommunicator::~DataBaseCommunicator()
{
    db.close();
}

DataBaseCommunicator *DataBaseCommunicator::getInstance(QObject *parent)
{
    if (instance == nullptr)
    {
        instance = new DataBaseCommunicator(parent);
    }

    return instance;
}

bool DataBaseCommunicator::checkLoginPassword(const QString &login, const QString &password)
{
    bool correctLoginPassword = false;

    QSqlQuery query(db);

    query.exec("SELECT Login, MdP FROM TCompte;");

    while (query.next())
    {
        if (query.value(0).toString().toStdString() == login.toStdString()
            && query.value(1).toString().toStdString() == password.toStdString())
        {
            correctLoginPassword = true;
        }
    }

    return correctLoginPassword;
}

void DataBaseCommunicator::addCustomerToDatabase(Ui::AddingClient * ui)
{
    QSqlQuery query(db);
    query.prepare("INSERT INTO TClient(Nom, Prenom, Adresse, Ville, CP, Commentaire, Tel, DateRdv, DureeRdv, Priorite) VALUES "
                          "(:NomAdd, :PrenomAdd, :AdresseAdd, :VilleAdd, :CPAdd, :CommentaireAdd, :TelAdd, :DateRdvAdd, :DureeRdvAdd, :PrioriteAdd)");
    query.bindValue(":NomAdd", ui->editName->text());
    query.bindValue(":PrenomAdd", ui->editFirstName->text());
    query.bindValue(":AdresseAdd", ui->editAddress->text());
    query.bindValue(":VilleAdd", ui->editCity->text());
    query.bindValue(":CPAdd", ui->editPostalCode->text());
    query.bindValue(":CommentaireAdd", ui->editComments->toPlainText());
    query.bindValue(":TelAdd", ui->editPhoneNumber->text().toInt());
    query.bindValue(":DateRdvAdd", ui->editDate->text());
    query.bindValue(":DureeRdvAdd", ui->editConsultingTime->text());
    query.bindValue(":PrioriteAdd", ui->priorityList->itemData(ui->priorityList->currentIndex()));

    if(!query.exec())
    {
        qDebug() << db.lastError().text();
        qDebug() << "Erreur à l'insersion de donnees client !\n";
    }
}
#include <iostream>
void DataBaseCommunicator::searchCustomerFromDatabase(int id, const QString &name, const QString &firstname)
{
    QSqlQuery query(db);

    query.prepare("SELECT Id, Nom, Prenom FROM TClient WHERE Id == :id OR Nom LIKE ':name%' OR Prenom LIKE ':firstname%';");

    query.bindValue(":id", id);
    query.bindValue(":name", name);
    query.bindValue(":firstName", firstname);

    query.exec();

    while (query.next())
    {
        std::cout << query.value(1).toString().toStdString();


    }
}
