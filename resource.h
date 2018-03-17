#ifndef RESOURCE_H
#define RESOURCE_H

#include <QObject>
#include <QString>

#include "type.h"

class Resource : public QObject
{
        Q_OBJECT
    public:
        explicit Resource(QObject *parent = nullptr);

        QString getName() const;
        QString getFirstName() const;
        Type * getType() const;

        void setName(const QString & value);
        void setFirstName(const QString & value);
        void setType(Type * value);

    private:
        QString name,
                firstName;

        Type * type;
};

#endif // RESOURCE_H
