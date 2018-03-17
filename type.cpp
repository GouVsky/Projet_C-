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
