#ifndef ADDINGEMPLOYEE_H
#define ADDINGEMPLOYEE_H

#include <QObject>
#include <QDialog>

#include "type.h"
#include "account.h"
#include "resource.h"
#include "customizedstring.h"
#include "databasecommunicator.h"

namespace Ui
{
    class addingEmployee;
}

class addingEmployee : public QDialog
{
    Q_OBJECT

    public:
        explicit addingEmployee(QWidget *parent = 0);
        ~addingEmployee();

    private slots:
        void on_QuitButton_clicked();

        void on_comboBox_currentTextChanged(const QString &arg1);

        void on_NomInput_textChanged(const QString &arg1);

        void on_PrenomInput_textChanged(const QString &arg1);

        void on_AddButton_clicked();

    signals:
        void addingSucceed(QString message);

    private:
        void enableOrDisableComputerScientistLayout(bool enabled);

        Ui::addingEmployee *ui;
        CustomizedString *utils;
};

#endif // ADDINGEMPLOYEE_H
