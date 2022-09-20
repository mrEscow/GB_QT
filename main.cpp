/*
     1. Создать программу-органайзер, в которую можно будет вводить задачи.
        Каждая задача состоит из следующих пунктов:
            ● название задачи
            ● дата окончания выполнения задачи (дедлайн - в формате dd.mm.yyyy)
            ● текущий прогресс (число от 0 до 10)

        С помощью QML создать графический интерфейс программы для ввода данных и кнопку для записи
        задачи.

        Предусмотреть возможность при закрытии программы сохранения всех введенных пользователем
        задач в файл, а при открытии подгрузить данные из файла.
        Последующие задачи дозаписывать в уже существующий файл. Отображать задачи в программе не надо.

    2. *Создать пользовательский виджет - кнопку в отдельном файле.
        Использовать эту кнопку в первом задании.
*/

#include <QResource>
#include <QGuiApplication>
#include <QQmlContext>
#include <QQmlApplicationEngine>
#include <QStringListModel>
#include "AppCore.h"


int main(int argc, char *argv[])
{
    QResource::registerResource("./Resource.qrc");
    QCoreApplication::setOrganizationName("Escow company");
    QCoreApplication::setApplicationName("TextEditor");

    AppCore appCore;

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/QML/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
        &app, [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        }, Qt::QueuedConnection);


    //qmlRegisterType<AppCore>("Escow company", 1, 0, "AppCore");


    engine.rootContext()->setContextProperty("appCore", &appCore);

    engine.load(url);
    return app.exec();

}
