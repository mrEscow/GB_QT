// Escow

/*
    Создать список с названиями языков программирования (С++, Python, Java, C#, PHP, JavaScript).
    Для каждого элемента списка рядом отобразить иконку с логотипом языка программирования.
    Предусмотреть возможно изменения текста в каждом элементе списка. Добавить возможность перемещения элементов в списке.
    Создать кнопку для добавления нового языка программирования в список.
    Иконку для него поставить любую (по-умолчанию).
    Создать кнопку для удаления элемента из списка (в этом случае элемент должен быть выбран).
    Создать CheckBox и когда будет стоять галочка, отобразить список в режиме иконок (нужен метод setViewMode()).
    Когда галочка не стоит, то список должен отображаться в обычном режиме.
    Подсказка: используйте справку qt, вызов F1.
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
