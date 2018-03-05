#include "client.h"

int Client::id = 0;


Client::Client(QString name, QString firstName, QObject *parent) : QObject(parent)
{
    id++;

    priority = 1;

    totalConsultingTime = 60;

    this->name = name;

    this->firstName = firstName;
}
