#include "mainwindow.h"
#include "identificationcontroller.h"
#include <QApplication>
#include <QMultiMap>
#include <QPair>
#include <iostream>
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
    std::cout << "Number of inserts : " << DataBaseCommunicator::getUiInsertCompteur();

    QMultiMap <int, QString> multiMap;

    multiMap.insert(1, "titi");
    multiMap.insert(4, "toto");
    multiMap.insert(3, "tutu");
    multiMap.insert(4, "tata");

    /*QMultiMap <int, QString>::iterator it = multiMap.begin();

    //multiMap.erase(it);


    for (it; it != multiMap.end(); it++)
    {
        //multiMap.remove(it.);

       std::cout <<  << std::endl;
    }*/

    multiMap.insert(0, "tete");

    return 0;
}
