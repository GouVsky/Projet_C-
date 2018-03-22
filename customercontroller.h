#ifndef CUSTOMERCONTROLLER_H
#define CUSTOMERCONTROLLER_H

#include <QObject>
#include <QVector>
#include <QDialog>
#include <QLineEdit>
#include <QMessageBox>

#include "customer.h"
#include "customizedstring.h"
#include "databasecommunicator.h"

namespace Ui
{
    class CustomerController;
}

class CustomerController : public QDialog
{
        Q_OBJECT

    public:
        CustomerController(QWidget *parent = 0);
        CustomerController(Customer *customer, int id, QWidget *parent = 0);
        ~CustomerController();
        bool checkRequiredInputs();

    private slots:
        void on_cancel_clicked();

        void on_add_clicked();

        void on_edit_clicked();

        void on_editName_textChanged(const QString &arg1);

        void on_editFirstName_textChanged(const QString &arg1);

        void on_editCity_textChanged(const QString &arg1);

    signals:
        void addingSucceed(QString message);
        void editingSucceed(QString message);

    private:
        void setCustomerFields();

        Ui::CustomerController *ui;
        CustomizedString *utils;
        Customer *customer;
};

#endif // CUSTOMERCONTROLLER_H
