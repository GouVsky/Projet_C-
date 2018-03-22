#ifndef PLANIFICATION_H
#define PLANIFICATION_H

#include <QObject>

class Planification : public QObject
{
        Q_OBJECT
    public:
        explicit Planification(QObject *parent = nullptr);
        //void sortCustomersByPriority();

    signals:

    public slots:
};

#endif // PLANIFICATION_H
