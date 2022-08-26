/*
    1. Добавить меню в текстовый редактор.

    2. Добавить в текстовый редактор кнопку для вывода на печать.

    3. Добавить в текстовый редактор поддержку многодокументного интерфейса.

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
