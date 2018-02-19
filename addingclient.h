#ifndef ADDINGCLIENT_H
#define ADDINGCLIENT_H

#include <QDialog>

namespace Ui {
    class AddingClient;
}

class AddingClient : public QDialog
{
        Q_OBJECT

    public:
        explicit AddingClient(QWidget *parent = 0);
        ~AddingClient();

    private:
        Ui::AddingClient *ui;
};

#endif // ADDINGCLIENT_H
