#include "client.h"

int Client::id = 0;


Client::Client(QObject *parent) : QObject(parent)
{
    id++;

    priority = 1;

    totalConsultingTime = 60;
}
