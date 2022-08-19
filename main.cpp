/*
    1. Написать собственный виджет - просмотрщик файловой системы.
       Добавить строку навигации, в которой выводится текущий каталог

    2. Добавить в текстовый редактор выбор из нескольких таблиц стилей.
       Сделать темную и светлую тему.
*/

#include "MainWindow.h"
#include "qdebug.h"
#include <QApplication>
#include <QTranslator>
#include <QResource>
#include <QFile>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QResource::registerResource("./Resource.rcc");
    MainWindow w;
    w.resize(800,600);
    w.show();
    return a.exec();
}
