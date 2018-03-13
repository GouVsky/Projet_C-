#ifndef SEARCHCUSTOMERCONTROLLER_H
#define SEARCHCUSTOMERCONTROLLER_H

#include <QObject>
#include "mainwindow.h"

class SearchCustomerController : public QObject
{
        Q_OBJECT
    public:
        explicit SearchCustomerController(QObject *parent = nullptr);
        bool checkOneFieldSearchCustomerFullAtLeast();
};

#endif // SEARCHCUSTOMERCONTROLLER_H
