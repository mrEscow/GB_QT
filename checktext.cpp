/*
    Написать класс, который будет вставлять в текст спецсимволы (4–5).
    Пригодится для символов, для которых нет клавиши на клавиатуре, но они часто используются в тексте:
        © — знак охраны авторского права,
        ‰ — промилле,
        ® - знак правовой охраны товарного знака,
        € — евро,
        ₽ — рубль.
    Например, ввод рубля в программе #@RUB@, или руб. (автоматически заменить на знак).
*/

#include "checktext.h"

CheckText::CheckText(QObject* parent) : QObject(parent)
{   

}

void CheckText::changeText(QString &input)
{
    input.replace(QString("знак охраны авторского права"),QString("©"));

    input.replace(QString("промилле"),QString("‰"));

    input.replace(QString("знак правовой охраны товарного знака"),QString("®"));

    input.replace(QString("EURO"),QString("€"));
    input.replace(QString("евро"),QString("€"));

    input.replace(QString("RUB"),QString("₽"));
    input.replace(QString("руб"),QString("₽"));


}
