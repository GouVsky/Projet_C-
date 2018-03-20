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

int DataBaseCommunicator::addCustomerToDatabase(Customer * client)
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

    return query.lastInsertId().toInt();
}

void DataBaseCommunicator::updateCustomer(Customer *customer)
{
    QSqlQuery query(db);

    query.prepare("UPDATE TClient SET Nom = :name, Prenom = :firstname, Adresse = :address, Ville = :city, CP = :postalCode, Commentaire = :comments, Tel = :phone, DateRdv = :dateRdv, DureeRdv = :consultingTime, Priorite = :priority WHERE Id == :id;");

    query.bindValue(":id", customer->getId());
    query.bindValue(":name", customer->getName());
    query.bindValue(":firstname", customer->getFirstName());
    query.bindValue(":address", customer->getAddress());
    query.bindValue(":city", customer->getCity());
    query.bindValue(":postalCode", customer->getPostalCode());
    query.bindValue(":comments", customer->getComments());
    query.bindValue(":phone", customer->getPhoneNumber());
    query.bindValue(":dateRdv", customer->getConsultingDay());
    query.bindValue(":consultingTime", customer->getDureeRDV());
    query.bindValue(":priority", customer->getPriority());

    query.exec();
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

void DataBaseCommunicator::displayEmployeeList(QTreeView * treeView)
{
    QSqlQuery query(db);
    QSqlQuery query2(db);
    query.prepare("SELECT DISTINCT Label FROM TType ORDER BY Label;");
    query2.prepare("SELECT Nom FROM TRessource, TType WHERE TRessource.IdType = TType.Id and Label LIKE :label ;");
    query.exec();

    QStandardItemModel * standardModel = new QStandardItemModel(treeView) ;
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
            typeNode->appendRow(nameNode);
        }
    }
    treeView->setModel(standardModel);
    treeView->expandAll();
}

Customer DataBaseCommunicator::getCustomer(int index)
{
    Customer customer;

    QSqlQuery query(db);

    query.prepare("SELECT * FROM TClient WHERE Id == :id");

    query.bindValue(":id", index);

    query.exec();

    query.next();

    customer.setName(query.value(1).toString());
    customer.setFirstName(query.value(2).toString());
    customer.setAddress(query.value(3).toString());
    customer.setCity(query.value(4).toString());
    customer.setPostalCode(query.value(5).toString());
    customer.setComments(query.value(6).toString());
    customer.setPhoneNumber(query.value(7).toInt());
    customer.setConsultingDay(query.value(8).toDate());
    customer.setDureeRDV(query.value(9).toInt());
    customer.setPriority(query.value(10).toInt());

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

    query.prepare("SELECT Nom, Prenom, Label FROM TRessource R, TType T WHERE R.IdType == T.Id;");

    query.exec();

    while (query.next())
    {
        resources.append(query.value(0).toString() + " " + query.value(1).toString() + " - " + query.value(2).toString());
    }

    return resources;
}

void DataBaseCommunicator::editEmployee(Resource oldEmployee, Resource newEmployee)
{
     QSqlQuery query(db);
     query.prepare("UPDATE TRessource SET Nom = ':newName', Prenom = ':newFirstName', IdType = ':newType' WHERE Nom LIKE :oldName");
     query.bindValue(":newName", newEmployee.getName());
     query.bindValue("newFirstName", newEmployee.getFirstName());
     query.bindValue("newType", newEmployee.getType());
     query.bindValue(":oldName", oldEmployee.getName());
}
Resource * DataBaseCommunicator::findEmployee(QString nomEmployee)
{
    QSqlQuery query(db);
    QSqlQuery queryType(db);
    query.prepare("SELECT * FROM TRessource WHERE Nom LIKE :employeeName");
    query.bindValue(":employeeName", nomEmployee);
    query.exec();
    query.next();
    queryType.prepare("SELECT * FROM TType WHERE Id == :id");
    queryType.bindValue(":id", query.value(3));
    queryType.exec();
    queryType.next();
    Resource * employeeEdited = new Resource();
    Type * typeEmployee = new Type();
    typeEmployee->setId(queryType.value(0).toInt());
    typeEmployee->setLabel(queryType.value(1).toString());

    employeeEdited->setFirstName(query.value(1).toString());
    employeeEdited->setName(query.value(2).toString());
    employeeEdited->setType(typeEmployee);
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
