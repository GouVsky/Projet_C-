#ifndef CLIENT_H
#define CLIENT_H

#include <QString>
#include <QObject>
#include <QDateTime>

class Client : public QObject
{
    Q_OBJECT

    public:
        Client(QString name, QString firstName, QObject *parent = nullptr);
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

#endif // CLIENT_H
