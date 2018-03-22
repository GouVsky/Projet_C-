#ifndef EDITEMPLOYEE_H
#define EDITEMPLOYEE_H

#include <QDialog>
#include "databasecommunicator.h"

namespace Ui {
class editemployee;
}

class editemployee : public QDialog
{
    Q_OBJECT

public:
    explicit editemployee(QWidget *parent = 0);
    explicit editemployee(int idEmploye, QWidget *parent = 0);
    ~editemployee();
    bool checkRequiredInputs();

private slots:
    void enableOrDisableComputerScientistLayout(bool enabled);
    void on_comboBox_currentTextChanged(const QString &arg1);

    void on_Buton_cancel_clicked();

    void on_Edit_buton_clicked();

private:
    Ui::editemployee *ui;
    int idEmployee;
};

#endif // EDITEMPLOYEE_H
