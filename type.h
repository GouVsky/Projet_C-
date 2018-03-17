#ifndef TYPE_H
#define TYPE_H

#include <QObject>
#include <QString>

class Type : public QObject
{
        Q_OBJECT
    public:
        explicit Type(QObject *parent = nullptr);

        int getId() const;
        QString getLabel() const;

        void setId(int value);
        void setLabel(const QString & value);

    private:
        int id;
        QString label;

    signals:

    public slots:
};

#endif // TYPE_H
