#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "identification.h"
#include "apropos.h"

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

private:
        Ui::MainWindow * ui;
        Identification * identificationDialog;
        apropos * aPropoDialog;
};

#endif // MAINWINDOW_H
