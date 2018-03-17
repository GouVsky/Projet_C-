#ifndef APROPOS_H
#define APROPOS_H

#include <QDialog>

namespace Ui
{
    class About;
}

class About : public QDialog
{
    Q_OBJECT

    public:
        explicit About(QWidget *parent = 0);
        ~About();


    private slots:
        void on_pushButton_clicked();

    private:
        Ui::About *ui;
};

#endif // APROPOS_H
