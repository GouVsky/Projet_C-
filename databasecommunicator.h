#ifndef DATABASECOMMUNICATOR_H
#define DATABASECOMMUNICATOR_H

#include <QObject>
#include <QVariant>
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlError>
#include <QTreeWidget>
#include <QStandardItemModel>
#include <QItemSelectionModel>
#include <QSqlQueryModel>
#include <QDate>
#include <QDir>
#include <QStringList>
#include <QInputDialog>
#include <QMessageBox>

#include "account.h"
#include "customer.h"
#include "resource.h"
#include "c_init_bd.h"
#include "editemployee.h"

class DataBaseCommunicator : public QObject
{
        Q_OBJECT
    public:
        static DataBaseCommunicator *getInstance(QObject *parent = nullptr);
        bool checkLoginPassword(const QString &login, const QString &password);
        int addCustomer(Customer *customer, bool exists = false);
        void deleteCustomer(int id);
        int addResourceToDatabase(Resource *resource);
        int addAccountToDatabase(Account *account, int resource);
        QSqlQueryModel *searchCustomerFromDatabase(const QString &id, const QString &name, const QString &firstname, const QDate &beginningDate, const QDate &endingDate);
        void displayEmployeeList(QTreeView *treeView);
        Customer getCustomer(int index);
        QStringList getTypesList();
        QStringList getResourcesTypesList();
        void editEmployee(Resource newEmployee, int idEmp);
        Resource  * findEmployee(int index);
        Account * getAccount(int idEmployee);
        void deleteEmployee(int idEmployee);
        void deleteRdv(int index);

    private:
        explicit DataBaseCommunicator(QObject *parent = nullptr);
        ~DataBaseCommunicator();

        QSqlDatabase db;
        static DataBaseCommunicator *instance;
        QSqlQueryModel * model;

    signals:

    public slots:
};

#endif // DATABASECOMMUNICATOR_H
