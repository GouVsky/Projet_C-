#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <QString>
#include <QDate>
#include <QList>

#include "resource.h"

class Customer
{
    public:
        Customer();
        QString getName() const;
        QString getFirstName() const;
        QString getAddress() const;
        QString getCity() const;
        QString getPostalCode() const;
        QString getComments() const;
        int getPhoneNumber() const;
        int getPriority() const;
        int getDureeRDV() const;
        QDate getConsultingDay() const;
        int getId() const;
        Resource getResource(int index) const;
        int getResourcesNumber() const;

        void setName(const QString &value);
        void setFirstName(const QString &value);
        void setAddress(const QString &value);
        void setCity(const QString &value);
        void setPostalCode(const QString &value);
        void setComments(const QString &value);
        void setPhoneNumber(int value);
        void setPriority(int value);
        void setDureeRDV(int value);
        void setConsultingDay(const QDate &value);
        void setId(int value);
        void setResource(Resource value);

    private:
        int id;

        QString name,
                firstName,
                address,
                city,
                postalCode,
                comments;

        int phoneNumber,
            Priority,
            DureeRDV;

        QDate consultingDay;

        QList <Resource> *resources;
};

#endif // CUSTOMER_H
