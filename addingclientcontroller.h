#ifndef ADDINGCLIENT_H
#define ADDINGCLIENT_H

#include <QObject>
#include <QDialog>
#include <QLineEdit>
#include <QMessageBox>

#include "customer.h"
#include "customizedstring.h"
#include "databasecommunicator.h"

namespace Ui {
    class AddingClient;
}

class AddingClient : public QDialog
{
        Q_OBJECT

    public:
        explicit AddingClient(QWidget *parent = 0);
        ~AddingClient();
        bool checkRequiredInputs();

    private slots:
        void on_cancel_clicked();

        void on_add_clicked();

        void on_editName_textChanged(const QString &arg1);

        void on_editFirstName_textChanged(const QString &arg1);

        void on_editCity_textChanged(const QString &arg1);

    signals:
        void addingSucceed(QString message);

    private:
        Ui::AddingClient *ui;
        CustomizedString *utils;
};

#endif // ADDINGCLIENT_H
