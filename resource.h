#ifndef RESOURCE_H
#define RESOURCE_H

#include <QString>

#include "type.h"

class Resource
{
    public:
        Resource();

        QString getName() const;
        QString getFirstName() const;
        Type * getType() const;
        int getId() const;

        void setName(const QString & value);
        void setFirstName(const QString & value);
        void setType(Type value);
        void setId(int value);

    private:
        int id;

        QString name,
                firstName;

        Type * type;
};

#endif // RESOURCE_H
