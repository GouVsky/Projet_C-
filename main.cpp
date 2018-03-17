#include "mainwindow.h"
#include "identificationcontroller.h"
#include <QApplication>

#include "databasecommunicator.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    C_INIT_BD::Creation_BD();

    DataBaseCommunicator::getInstance(&a);

    MainWindow w;

    Identification identification(&w);

    w.show();

    if (identification.exec() == QDialog::Accepted)
    {
        a.exec();
    }

    return 0;
}
