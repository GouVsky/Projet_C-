#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "aproposcontroller.h"
#include "addingclientcontroller.h"
#include "identificationcontroller.h"
#include "searchcustomercontroller.h"

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

    private:
        Ui::MainWindow * ui;
        Identification * identificationDialog;
        apropos * aProposDialog;
        AddingClient * addingClientDialog;
        SearchCustomerController * searchCustomerController;
};

#endif // MAINWINDOW_H
