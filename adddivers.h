#ifndef ADDDIVERS_H
#define ADDDIVERS_H

#include <QDialog>
#include "resource.h"
#include "type.h"
#include "databasecommunicator.h"

namespace Ui {
class AddDivers;
}

class AddDivers : public QDialog
{
    Q_OBJECT

public:
    explicit AddDivers(QWidget *parent = 0);
    ~AddDivers();

private slots:
    void on_OK_buton_clicked();

    void on_Cancel_Buton_clicked();

private:
    Ui::AddDivers *ui;
};

#endif // ADDDIVERS_H
