#ifndef ADDINGCLIENT_H
#define ADDINGCLIENT_H

#include <QDialog>
#include <QRegExp>
#include <QRegExpValidator>
#include <QLineEdit>

namespace Ui {
    class AddingClient;
}

class AddingClient : public QDialog
{
        Q_OBJECT

    public:
        explicit AddingClient(QWidget *parent = 0);
        ~AddingClient();
        void capitalize(const QString &str, QLineEdit *lineEdit);

    private slots:
        void on_cancel_clicked();

        void on_add_clicked();

        void on_editName_textChanged(const QString &arg1);

        void on_editFirstName_textChanged(const QString &arg1);

        void on_editCity_textChanged(const QString &arg1);

    private:
        Ui::AddingClient *ui;
        QRegExpValidator *phoneValidator,
                         *postalCodeValidator;
};

#endif // ADDINGCLIENT_H
