#ifndef IDENTIFICATION_H
#define IDENTIFICATION_H

#include <QDialog>
#include <QCloseEvent>
#include <QDesktopWidget>

namespace Ui
{
    class Identification;
}

class Identification : public QDialog
{
    Q_OBJECT

    public:
        explicit Identification(QWidget *parent = 0);
        ~Identification();

    private slots:
        void on_cancel_clicked();
        void on_connect_clicked();

    private:
        Ui::Identification *ui;
};

#endif // IDENTIFICATION_H
