#ifndef CLIENT_H
#define CLIENT_H

#include <QString>
#include <QObject>
#include <QDateTime>

class Client : public QObject
{
    Q_OBJECT

    public:
        explicit Client(QObject *parent = nullptr);

    private:
        QString * name,
                * firstName,
                * address,
                * postalCode,
                * city,
                * comments,
                * phoneNumber;

        int static id;

        int priority,
            totalConsultingTime;

        QDateTime * consultingDay;
};

#endif // CLIENT_H
