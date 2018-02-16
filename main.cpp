#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;

    Identification identification;

    w.show();

    if (identification.exec() == QDialog::Accepted)
    {
        a.exec();
    }

    return 0;
}
