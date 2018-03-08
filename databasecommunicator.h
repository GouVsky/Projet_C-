#ifndef DATABASECOMMUNICATOR_H
#define DATABASECOMMUNICATOR_H

#include <QObject>
#include <QVariant>
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlError>
#include "ui_addingclient.h"

#include "c_init_bd.h"

class DataBaseCommunicator : public QObject
{
        Q_OBJECT
    public:
        explicit DataBaseCommunicator(QObject *parent = nullptr);
        ~DataBaseCommunicator();
        bool checkLoginPassword(const QString &login, const QString &password);
        bool addClientToDatabase(Ui::AddingClient * ui);

    private:
        QSqlDatabase db;

    signals:

    public slots:
};

#endif // DATABASECOMMUNICATOR_H
