#include "resource.h"

Resource::Resource()
{
    type = new Type();
}

QString Resource::getName() const
{
    return name;
}

QString Resource::getFirstName() const
{
    return firstName;
}

Type * Resource::getType() const
{
    return type;
}

void Resource::setName(const QString & value)
{
    name = value;
}

void Resource::setFirstName(const QString & value)
{
    firstName = value;
}

void Resource::setType(Type value)
{
    *type = value;
}

int Resource::getIndexInCombobox() const
{
    return indexInCombobox;
}

void Resource::setIndexInCombobox(int value)
{
    indexInCombobox = value;
}
