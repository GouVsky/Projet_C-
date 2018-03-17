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
#include <QStringList>

#include "customer.h"
#include "resource.h"
#include "c_init_bd.h"

class DataBaseCommunicator : public QObject
{
        Q_OBJECT
    public:
        static DataBaseCommunicator *getInstance(QObject *parent = nullptr);
        bool checkLoginPassword(const QString &login, const QString &password);
        void addCustomerToDatabase(Customer *client);
        void addResourceToDatabase(Resource *resource);
        void searchCustomerFromDatabase(int id, const QString &name, const QString &firstname);
        QSqlQueryModel *searchCustomerFromDatabase(const QString &id, const QString &name, const QString &firstname, const QDate &beginningDate, const QDate &endingDate);
        void displayEmployeeList(QTreeView *treeView);
        QStringList getResourcesList();

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
