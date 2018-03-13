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

void DataBaseCommunicator::addCustomerToDatabase(Customer * Client)
{
    QSqlQuery query(db);
    query.prepare("INSERT INTO TClient(Nom, Prenom, Adresse, Ville, CP, Commentaire, Tel, DateRdv, DureeRdv, Priorite) VALUES "
                          "(:NomAdd, :PrenomAdd, :AdresseAdd, :VilleAdd, :CPAdd, :CommentaireAdd, :TelAdd, :DateRdvAdd, :DureeRdvAdd, :PrioriteAdd)");
    query.bindValue(":NomAdd", Client->getName());
    query.bindValue(":PrenomAdd", Client->getFirstName());
    query.bindValue(":AdresseAdd", Client->getAddress());
    query.bindValue(":VilleAdd", Client->getCity());
    query.bindValue(":CPAdd", Client->getPostalCode());
    query.bindValue(":CommentaireAdd", Client->getComments());
    query.bindValue(":TelAdd", Client->getPhoneNumber());
    query.bindValue(":DateRdvAdd", Client->getConsultingDay());
    query.bindValue(":DureeRdvAdd", Client->getDureeRDV());
    query.bindValue(":PrioriteAdd", Client->getPriority());

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
