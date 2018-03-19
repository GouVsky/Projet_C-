#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <QString>
#include <QDateTime>

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
        QDateTime getConsultingDay() const;

        void setName(const QString &value);
        void setFirstName(const QString &value);
        void setAddress(const QString &value);
        void setCity(const QString &value);
        void setPostalCode(const QString &value);
        void setComments(const QString &value);
        void setPhoneNumber(int value);
        void setPriority(int value);
        void setDureeRDV(int value);
        void setConsultingDay(const QDateTime &value);

private:
        QString name,
        firstName,
                address,
                city,
                postalCode,
                comments;

        int phoneNumber,
            Priority,
            DureeRDV;

        QDateTime consultingDay;
};

#endif // CUSTOMER_H
