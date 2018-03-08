#include "mainwindow.h"
#include <QApplication>

#include "databasecommunicator.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    C_INIT_BD::Creation_BD();

    MainWindow w;

    Identification identification;

    w.show();

    if (identification.exec() == QDialog::Accepted)
    {
        a.exec();
    }

    return 0;
}
