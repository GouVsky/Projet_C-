#include "account.h"

Account::Account(QObject *parent) : QObject(parent)
{

}

QString Account::getLogin() const
{
    return login;
}

QString Account::getPassword() const
{
    return password;
}

void Account::setLogin(const QString & value)
{
    login = value;
}

void Account::setPassword(const QString & value)
{
    password = value;
}

Resource * Account::getResource() const
{
    return resource;
}

void Account::setResource(Resource * value)
{
    resource = value;
}
