/*
    1. Добавить в текстовый редактор режим «Открыть только для чтения»,
       блокирующий любые правки для документа.

    2. Перевести текстовый редактор на английский язык (названия кнопок из предыдущих заданий).
       Добавить возможность динамически переключать языки во время работы приложения.

    3. Добавить в текстовый редактор возможность пользоваться сочетаниями клавиш:
        ctrl+o - открыть новый документ,
        ctrl+s - сохранить как,
        ctrl+n - создать новый документ,
        ctrl+q - выход из программы.
    Добавить возможность изменять дефолтные сочетания клавиш на пользовательские
        (например, действие открытие документа привязать к клавише F3).
*/

#include "MainWindow.h"
#include "qdebug.h"
#include <QApplication>
#include <QTranslator>
#include <QResource>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QResource::registerResource("./Resource.rcc");
    QTranslator translator;
    translator.load("languages/QtLanguage_" + QLocale::system().name());
    a.installTranslator(&translator);
    MainWindow w;
    w.resize(600,800);
    w.show();
    return a.exec();
}
