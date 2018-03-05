#ifndef RESOURCE_H
#define RESOURCE_H

#include <QObject>

class Resource : public QObject
{
        Q_OBJECT
    public:
        explicit Resource(int id, QString name, QObject *parent = nullptr);

    private:
        int id;
        QString name;
};

#endif // RESOURCE_H
