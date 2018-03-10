#include "addingpersoncontroller.h"

AddingPerson::AddingPerson(QWidget *parent) : QDialog(parent)
{

}

void AddingPerson::capitalize(const QString &str, QLineEdit *lineEdit)
{
    int position = lineEdit->cursorPosition();

    QString text = str;

    text = text.toLower();

    text[0] = text[0].toUpper();

    lineEdit->setText(text);

    lineEdit->setCursorPosition(position);
}

void AddingPerson::forbidNumericCaracteres(QLineEdit *lineEdit, int size)
{
    QString regexp = QString("[A-Za-z]{%1}").arg(size);

    QRegExp withoutNumbers(regexp);

    stringWithoutNumericCaracteresValidator = new QRegExpValidator(withoutNumbers, this);

    lineEdit->setValidator(stringWithoutNumericCaracteresValidator);
}

void AddingPerson::forbidAlphaCaracteres(QLineEdit *lineEdit, int size)
{
    QString regexp = QString("[0-9]{%1}").arg(size);

    QRegExp withoutLetters(regexp);

    stringWithoutAlphaCaracteresValidator = new QRegExpValidator(withoutLetters, this);

    lineEdit->setValidator(stringWithoutAlphaCaracteresValidator);
}
