#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "apropos.h"
#include "addingclient.h"
#include "identification.h"

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

    private:
        Ui::MainWindow * ui;
        Identification * identificationDialog;
        apropos * aPropoDialog;
        AddingClient * addingClientDialog;
};

#endif // MAINWINDOW_H
