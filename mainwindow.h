#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QTreeWidget>
#include <QSqlQueryModel>
#include <QStandardItemModel>
#include <QFileDialog>

#include "aboutcontroller.h"
#include "customercontroller.h"
#include "employeecontroller.h"
#include "databasecommunicator.h"
#include "editemployee.h"
#include "customizedstring.h"
#include "adddivers.h"

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
        void on_actionQuit_triggered();

        void on_actionAbout_triggered();

        void on_actionAddingCustomer_triggered();

        void on_actionAddingEmployee_triggered();

        void on_searchCustomerSearchButton_clicked();

        void on_searchCustomerEditButton_clicked();

        void on_searchCustomerDeleteButton_clicked();

        void on_showEmployeesRefreshButton_clicked();

        // Display a message in the status bar when some actions are realized.
        // The message is shown only for 5 seconds.
        void showMessageStatusBar(QString message);

        void on_customerNameSearch_textChanged(const QString &arg1);

        void on_customerFirstNameSearch_textChanged(const QString &arg1);

        void on_showEmployeesEditButton_clicked();

        void on_showEmployeesDeleteButton_clicked();

        void on_actionDivers_triggered();

        void on_Export_buton_clicked();

private:
        Ui::MainWindow *ui;
        CustomizedString *utils;
        QSqlQueryModel *model;
};

#endif // MAINWINDOW_H
