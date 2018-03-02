#ifndef SEARCHCLIENTCONTROLLER_H
#define SEARCHCLIENTCONTROLLER_H

#include <QObject>

#include "ui_mainwindow.h"

namespace Ui
{
    class MainWindow;
}

class searchClientController : public QObject
{
        Q_OBJECT
    public:
        explicit searchClientController(QObject *parent = nullptr);
        void checkOneFieldFullAtLeast(Ui::MainWindow * ui);

    private:
        Ui::MainWindow * ui;

    signals:

    public slots:
};

#endif // SEARCHCLIENTCONTROLLER_H
