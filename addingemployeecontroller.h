#ifndef ADDINGEMPLOYEE_H
#define ADDINGEMPLOYEE_H

#include <QDialog>

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

    private:
    Ui::addingEmployee *ui;
};

#endif // ADDINGEMPLOYEE_H
