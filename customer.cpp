#include "customer.h"

Customer::Customer()
{
    id = 0;
    resources = new QList <Resource> ();
}

QString Customer::getName() const
{
    return name;
}

QString Customer::getFirstName() const
{
    return firstName;
}

QString Customer::getAddress() const
{
    return address;
}

QString Customer::getCity() const
{
    return city;
}

QString Customer::getPostalCode() const
{
    return postalCode;
}

QString Customer::getComments() const
{
    return comments;
}

int Customer::getPhoneNumber() const
{
    return phoneNumber;
}

int Customer::getPriority() const
{
    return Priority;
}

int Customer::getDureeRDV() const
{
    return DureeRDV;
}

QDate Customer::getConsultingDay() const
{
    return consultingDay;
}

void Customer::setName(const QString &value)
{
    name = value;
}

void Customer::setFirstName(const QString &value)
{
    firstName = value;
}

void Customer::setAddress(const QString &value)
{
    address = value;
}

void Customer::setCity(const QString &value)
{
    city = value;
}

void Customer::setPostalCode(const QString &value)
{
    postalCode = value;
}

void Customer::setComments(const QString &value)
{
    comments = value;
}

void Customer::setPhoneNumber(int value)
{
    phoneNumber = value;
}

void Customer::setPriority(int value)
{
    Priority = value;
}

void Customer::setDureeRDV(int value)
{
    DureeRDV = value;
}

void Customer::setConsultingDay(const QDate &value)
{
    consultingDay = value;
}

int Customer::getId() const
{
    return id;
}

void Customer::setId(int value)
{
    id = value;
}

Resource Customer::getResource(int i) const
{
    return resources->at(i);
}

void Customer::setResource(Resource value)
{
    resources->push_back(value);
}

int Customer::getResourcesNumber() const
{
    return resources->size();
}
