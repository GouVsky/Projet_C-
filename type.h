#ifndef TYPE_H
#define TYPE_H

#include <QObject>
#include <QString>

class Type : public QObject
{
        Q_OBJECT
    public:
        explicit Type(QObject *parent = nullptr);

        QString getLabel() const;

        void setLabel(const QString & value);

    private:
        QString label;

    signals:

    public slots:
};

#endif // TYPE_H
