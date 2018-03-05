#ifndef DATABASECOMMUNICATOR_H
#define DATABASECOMMUNICATOR_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>

#include "c_init_bd.h"

class dataBaseCommunicator : public QObject
{
        Q_OBJECT
    public:
        explicit dataBaseCommunicator(QObject *parent = nullptr);

    signals:

    public slots:
};

#endif // DATABASECOMMUNICATOR_H
