#include "resource.h"

Resource::Resource(int id, QString name, QObject *parent) : QObject(parent)
{
    this->id = id;

    this->name = name;
}

