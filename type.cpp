#include "type.h"

Type::Type(QObject *parent) : QObject(parent)
{

}

QString Type::getLabel() const
{
    return label;
}

void Type::setLabel(const QString & value)
{
    label = value;
}

int Type::getId() const
{
    return id;
}

void Type::setId(int value)
{
    id = value;
}
