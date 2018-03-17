#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <QObject>
#include <QString>

#include "resource.h"

class Account : public QObject
{
        Q_OBJECT
    public:
        explicit Account(QObject *parent = nullptr);

        QString getLogin() const;
        QString getPassword() const;
        Resource * getResource() const;

        void setLogin(const QString & value);
        void setPassword(const QString & value);
        void setResource(Resource * value);

    private:
        QString login,
                password;

        Resource *resource;
};

#endif // ACCOUNT_H
