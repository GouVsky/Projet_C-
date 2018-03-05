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
    Ui::addingEmployee *ui;
};

#endif // ADDINGEMPLOYEE_H
