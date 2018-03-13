#ifndef CUSTOMER_H
#define CUSTOMER_H


class Customer
{
    public:
        Customer(QString name, QString firstName, QObject *parent = nullptr);
        void addAddress(QString address, QString postalCode, QString city);
        void addPhoneNumber(QString phoneNumber);
        void addComments(QString comments);

    private:
        QString name,
                firstName,
                address,
                postalCode,
                city,
                comments,
                phoneNumber;

        int static id;

        int priority,
            totalConsultingTime;

        QDateTime consultingDay;
};

#endif // CUSTOMER_H
