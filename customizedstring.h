#ifndef CUSTOMIZEDSTRING_H
#define CUSTOMIZEDSTRING_H

#include <QObject>
#include <QString>
#include <QRegExp>
#include <QLineEdit>
#include <QRegExpValidator>

class CustomizedString : public QObject
{
        Q_OBJECT
    public:
        explicit CustomizedString(QObject *parent = nullptr);
        void capitalize(const QString &str, QLineEdit *lineEdit);
        void forbidNumericCaracteres(QLineEdit *lineEdit, int size = 50);
        void forbidAlphaCaracteres(QLineEdit *lineEdit, int size = 50);

    private:
        QRegExpValidator *stringWithoutNumericCaracteresValidator,
                         *stringWithoutAlphaCaracteresValidator;
};

#endif // CUSTOMIZEDSTRING_H
