#ifndef TYPE_H
#define TYPE_H

#include <QString>

class Type
{
    public:
        Type();

        int getId() const;
        QString getLabel() const;

        void setId(int value);
        void setLabel(const QString & value);

    private:
        int id;
        QString label;
};

#endif // TYPE_H
