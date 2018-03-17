#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QTreeWidget>
#include <QSqlQueryModel>
#include "aproposcontroller.h"
#include "addingclientcontroller.h"
#include "addingemployeecontroller.h"
#include "databasecommunicator.h"
#include "editemployee.h"

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

    private:
        Ui::MainWindow * ui;
        apropos * aProposDialog;
        AddingClient * addingClientDialog;
        addingEmployee * addingEmployeeDialog;
        editemployee * EditEmployeeDialog;
};

#endif // MAINWINDOW_H
