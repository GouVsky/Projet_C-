#include "databasecommunicator.h"

DataBaseCommunicator *DataBaseCommunicator::instance = nullptr;


DataBaseCommunicator::DataBaseCommunicator(QObject *parent) : QObject(parent)
{
    db = QSqlDatabase::database("QSQLITE");

    db.open();

    model = new QSqlQueryModel;
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
QSqlQueryModel *DataBaseCommunicator::searchCustomerFromDatabase(int id, const QString &name, const QString &firstname, const QDateTime &beginningDate, const QDateTime &endingDate)
{
    QSqlQuery query(db);

    query.prepare("SELECT Id, Nom, Prenom, DateRdv FROM TClient WHERE Id == :id OR Nom LIKE '%'||:name||'%' OR Prenom LIKE '%'||:firstname||'%' OR (DateRdv >= :beginningDate AND DateRdv <= :endingDate);");

    query.bindValue(":id", id);
    query.bindValue(":name", name);
    query.bindValue(":firstName", firstname);
    query.bindValue(":beginningDate", beginningDate);
    query.bindValue(":endingDate", endingDate);

    query.exec();

    while (query.next())
    {
        model->setQuery(query);
    }
    return model;
}

void DataBaseCommunicator::displayEmployeeList(QTreeView * treeView)
{
    QStandardItemModel * standardModel = new QStandardItemModel(treeView) ;
    QStandardItem *rootNode = standardModel->invisibleRootItem();
    QStandardItem * typeNode= new QStandardItem("Type");
    QStandardItem * nameNode= new QStandardItem("Name");
    rootNode->appendRow(typeNode);
    rootNode->appendRow(nameNode);


    QSqlQuery query(db);
    query.prepare("SELECT Nom, Prenom FROM TRessource;");
    query.exec();
    while(query.next())
    {
        QStandardItem * treeViewType = new QStandardItem(query.value(0).toString());
        QStandardItem * treeViewName = new QStandardItem(query.value(0).toString());
        typeNode->appendRow(treeViewType);
        nameNode->appendRow(treeViewName);
        /*treeView->(0, query.value(0).toString());
        treeView->setText(1, query.value(1).toString());*/
    }
    treeView->setModel(standardModel);
    treeView->expandAll();

}

