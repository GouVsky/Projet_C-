#include "databasecommunicator.h"

DataBaseCommunicator *DataBaseCommunicator::instance = nullptr;


DataBaseCommunicator::DataBaseCommunicator(QObject *parent) : QObject(parent)
{
    db = QSqlDatabase::database();

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

int DataBaseCommunicator::addCustomerToDatabase(Customer * client, int idResource)
{
    QSqlQuery queryAddCustomer(db);
    QSqlQuery queryCreateRdv(db);

    queryAddCustomer.prepare("INSERT INTO TClient(Nom, Prenom, Adresse, Ville, CP, Commentaire, Tel, DateRdv, DureeRdv, Priorite) VALUES (:NomAdd, :PrenomAdd, :AdresseAdd, :VilleAdd, :CPAdd, :CommentaireAdd, :TelAdd, :DateRdvAdd, :DureeRdvAdd, :PrioriteAdd)");

    queryAddCustomer.bindValue(":NomAdd", client->getName());
    queryAddCustomer.bindValue(":PrenomAdd", client->getFirstName());
    queryAddCustomer.bindValue(":AdresseAdd", client->getAddress());
    queryAddCustomer.bindValue(":VilleAdd", client->getCity());
    queryAddCustomer.bindValue(":CPAdd", client->getPostalCode());
    queryAddCustomer.bindValue(":CommentaireAdd", client->getComments());
    queryAddCustomer.bindValue(":TelAdd", client->getPhoneNumber());
    queryAddCustomer.bindValue(":DateRdvAdd", client->getConsultingDay());
    queryAddCustomer.bindValue(":DureeRdvAdd", client->getDureeRDV());
    queryAddCustomer.bindValue(":PrioriteAdd", client->getPriority());

    queryCreateRdv.prepare("INSERT INTO TRdv(IdClient, IdRessource) VALUES (:customer, :resource)");

    queryCreateRdv.bindValue(":client", queryAddCustomer.lastInsertId().toInt());
    queryCreateRdv.bindValue(":resource", idResource);

    queryAddCustomer.exec();
    queryCreateRdv.exec();

    return queryAddCustomer.lastInsertId().toInt();
}

void DataBaseCommunicator::updateCustomer(Customer *customer)
{
    QSqlQuery queryUpdateCustomer(db);
    QSqlQuery queryUpdateRdv(db);

    queryUpdateCustomer.prepare("UPDATE TClient SET Nom = :name, Prenom = :firstname, Adresse = :address, Ville = :city, CP = :postalCode, Commentaire = :comments, Tel = :phone, DateRdv = :dateRdv, DureeRdv = :consultingTime, Priorite = :priority WHERE Id == :id;");

    queryUpdateCustomer.bindValue(":id", customer->getId());
    queryUpdateCustomer.bindValue(":name", customer->getName());
    queryUpdateCustomer.bindValue(":firstname", customer->getFirstName());
    queryUpdateCustomer.bindValue(":address", customer->getAddress());
    queryUpdateCustomer.bindValue(":city", customer->getCity());
    queryUpdateCustomer.bindValue(":postalCode", customer->getPostalCode());
    queryUpdateCustomer.bindValue(":comments", customer->getComments());
    queryUpdateCustomer.bindValue(":phone", customer->getPhoneNumber());
    queryUpdateCustomer.bindValue(":dateRdv", customer->getConsultingDay());
    queryUpdateCustomer.bindValue(":consultingTime", customer->getDureeRDV());
    queryUpdateCustomer.bindValue(":priority", customer->getPriority());

    queryUpdateCustomer.exec();

    queryUpdateRdv.prepare("UPDATE TRdv SET IdRessource = :resource WHERE IdClient = :customer;");

    queryUpdateRdv.bindValue(":customer", customer->getId());
    queryUpdateRdv.bindValue(":resource", customer->getResource()->getType()->getId());

    queryUpdateRdv.exec();
}

void DataBaseCommunicator::deleteCustomer(int id)
{
    QSqlQuery query(db);

    query.prepare("DELETE FROM TClient WHERE Id == :id");

    query.bindValue(":id", id);

    query.exec();
}

int DataBaseCommunicator::addResourceToDatabase(Resource *resource)
{
    QSqlQuery queryType(db);
    QSqlQuery queryResource(db);

    // We get the id of the type of the resource.

    queryType.prepare("SELECT Id FROM TType WHERE Id == :id");

    queryType.bindValue(":id", resource->getType()->getId());

    queryType.exec();

    queryType.next();


    queryResource.prepare("INSERT INTO TRessource (Nom, Prenom, IdType) VALUES (:name, :firstname, :idType)");

    queryResource.bindValue(":name", resource->getName());
    queryResource.bindValue(":firstname", resource->getFirstName());
    queryResource.bindValue(":idType", queryType.value(0).toInt());

    queryResource.exec();

    return queryResource.lastInsertId().toInt();
}

int DataBaseCommunicator::addAccountToDatabase(Account *account, int resource)
{
    QSqlQuery query;

    query.prepare("INSERT INTO TCompte (IdRessource, Login, MdP) VALUES (:resource, :login, :mdp)");

    query.bindValue(":resource", resource);
    query.bindValue(":login", account->getLogin());
    query.bindValue(":mdp", account->getPassword());

    query.exec();

    return query.lastInsertId().toInt();
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
#include <iostream>
void DataBaseCommunicator::displayEmployeeList(QTreeView * treeView)
{
    QSqlQuery query(db);
    QSqlQuery query2(db);
    query.prepare("SELECT DISTINCT Label FROM TType ORDER BY Label;");
    query2.prepare("SELECT Nom, TRessource.Id FROM TRessource, TType WHERE TRessource.IdType = TType.Id and Label LIKE :label ;");
    query.exec();

    QStandardItemModel * standardModel = new QStandardItemModel(treeView) ;
    standardModel->setColumnCount(2);
    QStandardItem *rootNode = standardModel->invisibleRootItem();
    while(query.next())
    {
        QStandardItem * typeNode= new QStandardItem(query.value(0).toString());
        rootNode->appendRow(typeNode);
        query2.bindValue(":label", query.value(0).toString());
        query2.exec();
        while(query2.next())
        {
            QStandardItem * nameNode= new QStandardItem(query2.value(0).toString());
            QStandardItem * idNode= new QStandardItem(query2.value(1).toString());
            //typeNode->appendRow(nameNode);
            typeNode->appendRow(QList<QStandardItem *>() << nameNode << idNode);
        }
    }

    treeView->setModel(standardModel);
    treeView->expandAll();
    treeView->hideColumn(1);
}

Customer DataBaseCommunicator::getCustomer(int index)
{
    Customer customer;

    QSqlQuery queryGetCustomer(db);

    queryGetCustomer.prepare("SELECT C.*, R.* FROM TClient C, TRessource R, TRdv RDV WHERE C.Id == :id AND C.Id == RDV.IdClient AND R.Id == RDV.IdRessource");

    queryGetCustomer.bindValue(":id", index);

    queryGetCustomer.exec();

    queryGetCustomer.next();

    customer.setName(queryGetCustomer.value(1).toString());
    customer.setFirstName(queryGetCustomer.value(2).toString());
    customer.setAddress(queryGetCustomer.value(3).toString());
    customer.setCity(queryGetCustomer.value(4).toString());
    customer.setPostalCode(queryGetCustomer.value(5).toString());
    customer.setComments(queryGetCustomer.value(6).toString());
    customer.setPhoneNumber(queryGetCustomer.value(7).toInt());
    customer.setConsultingDay(queryGetCustomer.value(8).toDate());
    customer.setDureeRDV(queryGetCustomer.value(9).toInt());
    customer.setPriority(queryGetCustomer.value(10).toInt());

    customer.getResource()->getType()->setId(queryGetCustomer.value(11).toInt());
    customer.getResource()->setName(queryGetCustomer.value(12).toString());
    customer.getResource()->setFirstName(queryGetCustomer.value(13).toString());

    return customer;
}

QStringList DataBaseCommunicator::getTypesList()
{
    QStringList types;

    QSqlQuery query(db);

    query.prepare("SELECT Label FROM TType");

    query.exec();

    while (query.next())
    {
        types.append(query.value(0).toString());
    }

    return types;
}

QStringList DataBaseCommunicator::getResourcesTypesList()
{
    QStringList resources;

    QSqlQuery query(db);

    query.prepare("SELECT T.Id, Nom, Prenom, Label FROM TRessource R, TType T WHERE R.IdType == T.Id;");

    query.exec();

    while (query.next())
    {
        resources.append("[" + query.value(0).toString() + "]"
                         + " " + query.value(1).toString() + " " + query.value(2).toString()
                         + " - " + query.value(3).toString());
    }

    return resources;
}

void DataBaseCommunicator::editEmployee(Resource oldEmployee, Resource newEmployee)
{
     QSqlQuery query(db);
     query.prepare("UPDATE TRessource SET Nom = ':newName', Prenom = ':newFirstName', IdType = ':newType' WHERE Nom LIKE :oldName");
     query.bindValue(":newName", newEmployee.getName());
     query.bindValue("newFirstName", newEmployee.getFirstName());
     query.bindValue("newType", newEmployee.getType()->getId());
     query.bindValue(":oldName", oldEmployee.getName());
}

Resource DataBaseCommunicator::findEmployee(int index)
{
    QSqlQuery query(db);
    QSqlQuery queryType(db);

    queryType.prepare("SELECT * FROM TType WHERE Id == :id");
    queryType.bindValue(":id", index);
    queryType.exec();

    query.prepare("SELECT * FROM TRessource WHERE IdType == :id");
    query.bindValue(":id", index);
    query.exec();
    query.next();

    queryType.next();
    Resource employeeEdited;
    Type typeEmployee;
    typeEmployee.setId(queryType.value(0).toInt());
    typeEmployee.setLabel(queryType.value(1).toString());

    employeeEdited.setName(query.value(1).toString());
    employeeEdited.setFirstName(query.value(2).toString());
    employeeEdited.setType(typeEmployee);
    return employeeEdited;
}

Account * DataBaseCommunicator::getAccount(QString nomEmployee)
{
    Account * infoAccount = new Account();
     QSqlQuery query(db);
     query.prepare("SELECT * FROM TCompte C, TRessource R WHERE C.IdRessource= R.Id AND R.Nom LIKE :employeeName");
     query.bindValue(":employeeName", nomEmployee);
     query.exec();
     query.next();
     infoAccount->setLogin(query.value(2).toString());
     infoAccount->setPassword(query.value(3).toString());

     return infoAccount;
}

void DataBaseCommunicator::deleteEmployee(QString nameEmployee)
{
    QSqlQuery query(db);
    query.prepare("DELETE FROM TRessource WHERE Nom LIKE :nameToDel");
    query.bindValue(":nameToDel", nameEmployee);
    query.exec();
}
