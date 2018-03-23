#ifndef EMPLOYEECONTROLLER_H
#define EMPLOYEECONTROLLER_H

#include <QObject>
#include <QDialog>

#include "type.h"
#include "account.h"
#include "resource.h"
#include "customizedstring.h"
#include "databasecommunicator.h"

namespace Ui
{
    class EmployeeController;
}

class EmployeeController : public QDialog
{
    Q_OBJECT

    public:
        explicit EmployeeController(QWidget *parent = 0);
        ~EmployeeController();
        bool checkRequiredInputs();

    private slots:
        void on_QuitButton_clicked();

        void on_comboBox_currentTextChanged(const QString &arg1);

        void on_NomInput_textChanged(const QString &arg1);

        void on_PrenomInput_textChanged(const QString &arg1);

        void on_AddButton_clicked();

    signals:
        void addingSucceed(QString message);

    private:
        // If the resource is an computer scientist, we enable the information concerning it.
        // Else, we disable it.
        void enableOrDisableComputerScientistLayout(bool enabled);

        Ui::EmployeeController *ui;
        CustomizedString *utils;
};

#endif // EMPLOYEECONTROLLER_H
