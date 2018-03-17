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

void DataBaseCommunicator::addCustomerToDatabase(Customer * client)
{
    QSqlQuery query(db);

    query.prepare("INSERT INTO TClient(Nom, Prenom, Adresse, Ville, CP, Commentaire, Tel, DateRdv, DureeRdv, Priorite) VALUES (:NomAdd, :PrenomAdd, :AdresseAdd, :VilleAdd, :CPAdd, :CommentaireAdd, :TelAdd, :DateRdvAdd, :DureeRdvAdd, :PrioriteAdd)");

    query.bindValue(":NomAdd", client->getName());
    query.bindValue(":PrenomAdd", client->getFirstName());
    query.bindValue(":AdresseAdd", client->getAddress());
    query.bindValue(":VilleAdd", client->getCity());
    query.bindValue(":CPAdd", client->getPostalCode());
    query.bindValue(":CommentaireAdd", client->getComments());
    query.bindValue(":TelAdd", client->getPhoneNumber());
    query.bindValue(":DateRdvAdd", client->getConsultingDay());
    query.bindValue(":DureeRdvAdd", client->getDureeRDV());
    query.bindValue(":PrioriteAdd", client->getPriority());

    if(!query.exec())
    {
        qDebug() << db.lastError().text();
        qDebug() << "Erreur à l'insersion de donnees client !\n";
    }
}

void DataBaseCommunicator::addEmployeeToDatabase(Resource *resource)
{
    QSqlQuery queryType(db);
    QSqlQuery queryResource(db);

    // We get the id of the type of the resource.

    /*queryType.prepare("SELECT Id FROM TType WHERE Label == :label");

    queryType.bindValue(":label", resource->getType()->getLabel());

    queryType.exec();*/


    queryResource.prepare("INSERT INTO TRessource (Nom, Prenom, IdType) VALUES (:name, :firstname, :idType)");

    queryResource.bindValue(":name", resource->getName());
    queryResource.bindValue(":firstname", resource->getFirstName());
    queryResource.bindValue(":idType", 1/*queryType.value(0)*/);

    queryResource.exec();
}

QSqlQueryModel *DataBaseCommunicator::searchCustomerFromDatabase(const QString &id, const QString &name, const QString &firstname, const QDate &beginningDate, const QDate &endingDate)
{
    QSqlQuery query(db);

    query.prepare("SELECT Id, Nom, Prenom, DateRdv FROM TClient WHERE Id == :id OR Nom LIKE :name||'%' OR Prenom LIKE :firstname||'%' OR (DateRdv BETWEEN :beginningDate AND :endingDate);");

    query.bindValue(":id", id.isEmpty() ? nullptr : id);
    query.bindValue(":name", name.isEmpty() ? nullptr : name);
    query.bindValue(":firstname", firstname.isEmpty() ? nullptr : firstname);
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
