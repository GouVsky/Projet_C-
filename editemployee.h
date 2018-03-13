#ifndef EDITEMPLOYEE_H
#define EDITEMPLOYEE_H

#include <QDialog>

namespace Ui {
class editemployee;
}

class editemployee : public QDialog
{
    Q_OBJECT

public:
    explicit editemployee(QWidget *parent = 0);
    ~editemployee();

private:
    Ui::editemployee *ui;
};

#endif // EDITEMPLOYEE_H
