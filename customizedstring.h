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

        // We force the upper case of the first character of the string
        // And the lower case of the other ones.
        void capitalize(const QString &str, QLineEdit *lineEdit);

        // We force the use of only numeric characters.
        // The method uses a regexp.
        void forbidNumericCaracteres(QLineEdit *lineEdit, int size = 50);

        // We force the use of only alpha characters.
        // The method uses a regexp.
        void forbidAlphaCaracteres(QLineEdit *lineEdit, int size = 50);

    private:
        QRegExpValidator *stringWithoutNumericCaracteresValidator,
                         *stringWithoutAlphaCaracteresValidator;
};

#endif // CUSTOMIZEDSTRING_H
