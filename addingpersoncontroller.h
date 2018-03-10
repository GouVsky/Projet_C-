#ifndef ADDINGPERSON_H
#define ADDINGPERSON_H

#include <QDialog>
#include <QRegExp>
#include <QLineEdit>
#include <QRegExpValidator>

class AddingPerson : public QDialog
{
        Q_OBJECT
    public:
        explicit AddingPerson(QWidget *parent = nullptr);
        void capitalize(const QString &str, QLineEdit *lineEdit);
        void forbidNumericCaracteres(QLineEdit *lineEdit, int size = 50);
        void forbidAlphaCaracteres(QLineEdit *lineEdit, int size = 50);

    private:
        QRegExpValidator *stringWithoutNumericCaracteresValidator,
                         *stringWithoutAlphaCaracteresValidator;

    signals:

    public slots:
};

#endif // ADDINGPERSON_H
