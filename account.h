#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <QObject>
#include <QString>

class Account : public QObject
{
        Q_OBJECT
    public:
        explicit Account(QObject *parent = nullptr);

        QString getLogin() const;
        QString getPassword() const;

        void setLogin(const QString & value);
        void setPassword(const QString & value);

    private:
        QString login,
                password;
};

#endif // ACCOUNT_H
