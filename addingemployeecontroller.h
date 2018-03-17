#ifndef ADDINGEMPLOYEE_H
#define ADDINGEMPLOYEE_H

#include <QObject>
#include <QDialog>

#include "customizedstring.h"

namespace Ui {
class addingEmployee;
}

class addingEmployee : public QDialog
{
    Q_OBJECT

    public:
        explicit addingEmployee(QWidget *parent = 0);
        ~addingEmployee();

    private:
        void enableOrDisableComputerScientistLayout(bool enabled);

    private slots:
        void on_QuitButton_clicked();

        void on_comboBox_currentIndexChanged(int index);

        void on_NomInput_textChanged(const QString &arg1);

        void on_PrenomInput_textChanged(const QString &arg1);

    private:
        Ui::addingEmployee *ui;
        CustomizedString *utils;
};

#endif // ADDINGEMPLOYEE_H
