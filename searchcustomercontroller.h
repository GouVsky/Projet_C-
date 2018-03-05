#ifndef SEARCHCUSTOMERCONTROLLER_H
#define SEARCHCUSTOMERCONTROLLER_H

#include <QObject>

#include "ui_mainwindow.h"

class SearchCustomerController : public QObject
{
        Q_OBJECT
    public:
        explicit SearchCustomerController(QObject *parent = nullptr);
        bool checkOneFieldSearchCustomerFullAtLeast(Ui::MainWindow * ui);
};

#endif // SEARCHCUSTOMERCONTROLLER_H
