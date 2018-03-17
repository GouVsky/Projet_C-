#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QTreeWidget>
#include <QSqlQueryModel>

#include "aboutcontroller.h"
#include "addingcustomercontroller.h"
#include "addingemployeecontroller.h"
#include "databasecommunicator.h"
#include "editemployee.h"
#include "customizedstring.h"

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
        explicit MainWindow(QWidget * parent = 0);
        ~MainWindow();

    private slots:
        void on_actionA_propos_triggered();

        void on_actionClient_triggered();

        void on_actionQuitter_triggered();

        void on_searchCustomerButton_clicked();

        void on_actionPersonnel_triggered();

        void on_EditButton_clicked();

        void on_DeleteButton_clicked();

        void showMessageStatusBar(QString message);

        void on_RefreshButon_clicked();

        void on_customerNameSearch_textChanged(const QString &arg1);

        void on_customerFirstNameSearch_textChanged(const QString &arg1);

    private:
        Ui::MainWindow * ui;
        About * aboutDialog;
        AddingCustomer * addingCustomerDialog;
        addingEmployee * addingEmployeeDialog;
        editemployee * editEmployeeDialog;
        CustomizedString *utils;
};

#endif // MAINWINDOW_H
