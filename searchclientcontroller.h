#ifndef SEARCHCLIENTCONTROLLER_H
#define SEARCHCLIENTCONTROLLER_H

#include <QObject>

class searchClientController : public QObject
{
        Q_OBJECT
    public:
        explicit searchClientController(QObject *parent = nullptr);

    private:
        void checkOneFieldFullAtLeast();

    signals:

    public slots:
};

#endif // SEARCHCLIENTCONTROLLER_H
