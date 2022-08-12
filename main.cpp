/*
 *   Ваш первый проект на данном курсе - текстовый редактор.
 *
 *   Добавьте на форму виджет текстового редактора.
 *
 *   Добавьте две кнопки: сохранить и открыть.
 *
 *   Предоставьте возможность пользователю выбрать куда сохранять файл и какой файл открывать.
 *
 *   Добавьте в текстовый редактор справку.
 *
 *   Текстовый файл с описанием разместить в ресурсах программы.
 *
 *   Для вызова справки разместить на форме соответствующую кнопку.
*/

#include "MainWindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.resize(600,800);
    w.show();
    return a.exec();
}
