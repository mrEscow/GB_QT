/*

    1. Добавить в текстовый редактор возможность вставлять дату и время в текст по позиции курсора.

    2. В проект файловый менеджер добавить возможность поиска папки или файла по имени.
       Поиск должен выполнятся во вторичном потоке.

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
    QApplication::setOrganizationName("Escow company");
    QApplication::setApplicationName("TextEditor");
    QResource::registerResource("./Resource.rcc");
    MainWindow w;
    w.resize(800,600);
    w.show();
    return a.exec();
}
