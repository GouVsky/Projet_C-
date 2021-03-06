#include "databasecommunicator.h"
unsigned int DataBaseCommunicator::uiInsertCompteur=0;
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

int DataBaseCommunicator::addCustomer(Customer *customer, bool exists)
{
    QSqlQuery queryCustomer(db);
    QSqlQuery queryRdv(db);

    // The request for an update of the customer.

    if (exists)
    {
         queryCustomer.prepare("UPDATE TClient SET Nom = :name, Prenom = :firstname, Adresse = :address, Ville = :city, CP = :postalCode, Commentaire = :comments, Tel = :phone, DateRdv = :dateRdv, DureeRdv = :consultingTime, Priorite = :priority WHERE Id == :id;");
    }

    // The request if the user wants to add a new customer.

    else
    {
        queryCustomer.prepare("INSERT INTO TClient(Nom, Prenom, Adresse, Ville, CP, Commentaire, Tel, DateRdv, DureeRdv, Priorite) VALUES (:name, :firstname, :address, :city, :postalCode, :comments, :phone, :dateRdv, :consultingTime, :priority)");
        uiInsertCompteur++;
    }

    queryCustomer.bindValue(":id", customer->getId());
    queryCustomer.bindValue(":name", customer->getName());
    queryCustomer.bindValue(":firstname", customer->getFirstName());
    queryCustomer.bindValue(":address", customer->getAddress());
    queryCustomer.bindValue(":city", customer->getCity());
    queryCustomer.bindValue(":postalCode", customer->getPostalCode());
    queryCustomer.bindValue(":comments", customer->getComments());
    queryCustomer.bindValue(":phone", customer->getPhoneNumber());
    queryCustomer.bindValue(":dateRdv", customer->getConsultingDay());
    queryCustomer.bindValue(":consultingTime", customer->getDureeRDV());
    queryCustomer.bindValue(":priority", customer->getPriority());

    queryCustomer.exec();

    queryRdv.prepare("INSERT INTO TRdv(IdRessource, IdClient) VALUES(:resource, :customer);");

    queryRdv.bindValue(":customer", (exists) ? customer->getId() : queryCustomer.lastInsertId().toInt());

    for (int i = 0; i < customer->getResourcesNumber(); i++)
    {
        queryRdv.bindValue(":resource", customer->getResource(i).getId());

        queryRdv.exec();
        uiInsertCompteur++;
    }

    return queryCustomer.lastInsertId().toInt();
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
    uiInsertCompteur++;

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
    uiInsertCompteur++;

    return query.lastInsertId().toInt();
}

QSqlQueryModel *DataBaseCommunicator::searchCustomerFromDatabase(const QString &id, const QString &name, const QString &firstname, const QDate &beginningDate, const QDate &endingDate)
{
    QSqlQuery query(db);

    query.prepare("SELECT Id, Nom, Prenom, DateRdv FROM TClient WHERE Id == :id OR Nom LIKE :name||'%' OR Prenom LIKE :firstname||'%' OR (DateRdv BETWEEN :beginningDate AND :endingDate) ORDER BY Nom ASC;");

    query.bindValue(":id", id.isEmpty() ? nullptr : id);
    query.bindValue(":name", name.isEmpty() ? nullptr : name);
    query.bindValue(":firstname", firstname.isEmpty() ? nullptr : firstname);
    query.bindValue(":beginningDate", beginningDate);
    query.bindValue(":endingDate", endingDate);

    query.exec();

    // The method returns a model containing the id fields, the name one, the first name and the date of rendez-vous.

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
            nameNode->setData(QVariant(query2.value(1).toString()), Qt::UserRole);
            typeNode->appendRow(nameNode);
        }
    }

    treeView->setModel(standardModel);
    treeView->setColumnWidth(0,400);
    treeView->expandAll();
}

Customer DataBaseCommunicator::getCustomer(int index)
{
    Customer customer;

    QSqlQuery queryGetCustomer(db);

    queryGetCustomer.prepare("SELECT C.*, R.*, T.* FROM TClient C, TRessource R, TType T, TRdv RDV WHERE C.Id == :id AND C.Id == RDV.IdClient AND R.Id == RDV.IdRessource");

    queryGetCustomer.bindValue(":id", index);

    queryGetCustomer.exec();

    while (queryGetCustomer.next())
    {
        customer.setId(index);
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

        Type type;

        type.setId(queryGetCustomer.value(14).toInt());
        type.setLabel(queryGetCustomer.value(16).toString());

        Resource resource;

        resource.setId(queryGetCustomer.value(11).toInt());
        resource.setName(queryGetCustomer.value(12).toString());
        resource.setFirstName(queryGetCustomer.value(13).toString());
        resource.setType(type);

        customer.setResource(resource);
    }

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

    query.prepare("SELECT R.Id, Nom, Prenom, Label FROM TRessource R, TType T WHERE R.IdType == T.Id;");

    query.exec();

    while (query.next())
    {
        // We display resources like "[id] name firstname - type".

        resources.append("[" + query.value(0).toString() + "]"
                         + " " + query.value(1).toString() + " " + query.value(2).toString()
                         + " - " + query.value(3).toString());
    }

    return resources;
}

void DataBaseCommunicator::editEmployee(Resource newEmployee, int idEmp)
{
     QSqlQuery query(db);
     QSqlQuery typeQuery(db);

     typeQuery.prepare("SELECT Id FROM TType WHERE Label LIKE :typeName");
     typeQuery.bindValue(":typeName", newEmployee.getType()->getLabel());
     typeQuery.exec();
     typeQuery.next();

     query.prepare("UPDATE TRessource SET Nom = :newFirstName, Prenom = :newName, IdType = :newType WHERE Id == :idEmp");
     query.bindValue(":newName", newEmployee.getName());
     query.bindValue(":newFirstName", newEmployee.getFirstName());
     query.bindValue(":newType", typeQuery.value(0).toInt());
     query.bindValue(":idEmp", idEmp);
     query.exec();
}

Resource * DataBaseCommunicator::findEmployee(int index)
{
    QSqlQuery query(db);
    QSqlQuery queryType(db);

    query.prepare("SELECT * FROM TRessource WHERE Id == :id");
    query.bindValue(":id", index);
    query.exec();
    query.next();

    queryType.prepare("SELECT * FROM TType WHERE Id == :id");
    queryType.bindValue(":id", query.value(3).toInt());
    queryType.exec();
    queryType.next();

    Resource * employeeEdited= new Resource();
    Type typeEmployee;
    typeEmployee.setId(queryType.value(0).toInt());
    typeEmployee.setLabel(queryType.value(1).toString());

    employeeEdited->setId(query.value(0).toInt());
    employeeEdited->setName(query.value(1).toString());
    employeeEdited->setFirstName(query.value(2).toString());
    employeeEdited->setType(typeEmployee);
    return employeeEdited;
}

Account * DataBaseCommunicator::getAccount(int idEmployee)
{
    Account * infoAccount = new Account();
     QSqlQuery query(db);
     query.prepare("SELECT * FROM TCompte WHERE IdRessource == :employeeid");
     query.bindValue(":employeeid", idEmployee);
     query.exec();
     query.next();
     infoAccount->setLogin(query.value(2).toString());
     infoAccount->setPassword(query.value(3).toString());

     return infoAccount;
}

void DataBaseCommunicator::deleteEmployee(int idEmployee)
{
    QSqlQuery query(db);
    query.prepare("DELETE FROM TRessource WHERE Id == :IdToDel");
    query.bindValue(":IdToDel", idEmployee);
    query.exec();
}

void DataBaseCommunicator::deleteRdv(int index)
{
    QSqlQuery query(db);

    query.prepare("DELETE FROM TRdv WHERE IdClient == :id");

    query.bindValue(":id", index);

    query.exec();
}

void DataBaseCommunicator::updateAccount(Account * acountToUpdate, int idEmployee)
{
    QSqlQuery query(db);
    QSqlQuery query2(db);
    query.prepare("UPDATE TCompte SET Login =:newLog, MdP=:newMdp WHERE IdRessource= :idEmp");
    query.bindValue(":newLog", acountToUpdate->getLogin());
    query.bindValue(":newMdp", acountToUpdate->getPassword());
    query.bindValue(":idEmp", idEmployee);
    query.exec();
    if(!query.next())
    {
        query2.prepare("INSERT INTO TCompte (IdRessource, Login, MdP) VALUES (:idEmp, :newLog, :newMdp)");
        query2.bindValue(":newLog", acountToUpdate->getLogin());
        query2.bindValue(":newMdp", acountToUpdate->getPassword());
        query2.bindValue(":idEmp", idEmployee);
        query2.exec();
        uiInsertCompteur++;
    }

}

unsigned int DataBaseCommunicator::getUiInsertCompteur()
{
    return uiInsertCompteur;
}

void DataBaseCommunicator::insertDivers(Resource employeeDivers)
{
    QSqlQuery query(db);
    QSqlQuery query2(db);
    query.prepare("INSERT INTO TRessource (Nom, Prenom, IdType) VALUES (:name, :firstname, :idType)");
    query2.prepare("SELECT Id FROM TType WHERE Label LIKE :nomType");
    query2.bindValue(":nomType", employeeDivers.getType()->getLabel());
    query2.exec();
    query2.next();
    query.bindValue(":name", employeeDivers.getName());
    query.bindValue(":firstname", employeeDivers.getFirstName());
    query.bindValue(":idType", query2.value(0).toInt());
    query.exec();
}

void DataBaseCommunicator::exportXML(QString fileName)
{
    QFile file(fileName);

    if (!file.open(QFile::WriteOnly | QFile::Text))
    {
        file.close();
        return;
    }

    QDomDocument xml("TRessource");

    QSqlQuery query(db);
    query.prepare("SELECT * FROM TRessource");
    query.exec();

    QDomElement masterRoot = xml.createElement("TRessource");
    xml.appendChild(masterRoot);

    while(query.next())
    {
        QDomElement root = xml.createElement("Ressource");
        root.setAttribute("id", query.value(0).toString());
        masterRoot.appendChild(root);

        QDomElement name = xml.createElement("Nom");
        root.appendChild(name);
        QDomText textName = xml.createTextNode(query.value(1).toString());
        name.appendChild(textName);

        QDomElement firstname = xml.createElement("Prenom");
        root.appendChild(firstname);
        QDomText textFirstName = xml.createTextNode(query.value(2).toString());
        firstname.appendChild(textFirstName);
    }

    QTextStream output(&file);

    output << xml.toString();

    file.close();
}
