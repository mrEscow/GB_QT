// Escow

/*
    Создать таблицу со столбцами: No, Имя компьютера, IP адрес, MAC адрес.
    Заполнить таблицу данными.
    Предусмотреть возможность нескольких строк в таблице (они могут идти не подряд).
    Для выделенных строк, по нажатию на кнопку покрасить задний фон в другой цвет.
*/

#include "MainWindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
