//-------------------------------------------------------------------------------------------------------------------------------//
//   Вариант на TCP с сервером.
//   При запуске клиента пользователь вводит свой никнейм, и клиент сразу устанавливает связь с сервером.
//   Сообщение от клиента отправляется на сервер и далее сервером пересылается на все остальные клиенты, подключенные к серверу.
//   Также при коннекте сервер оправляет клиенту последние 10 сообщений, которые были в чате до его подключения.                                  //
//-------------------------------------------------------------------------------------------------------------------------------//
#include "ChatClient.h"
#include <QQmlContext>
#include <QtQuick/QQuickView>
#include <QGuiApplication>
#include <QQmlApplicationEngine>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
        &app, [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        }, Qt::QueuedConnection);


    qmlRegisterType<ChatClient>("EscowCompany", 1, 0, "ChatClient");

    engine.load(url);

//    QQuickView view;
//    view.setResizeMode(QQuickView::SizeRootObjectToView);
//    view.setSource(QUrl(QStringLiteral("qrc:/main.qml")));
//    view.resize(480,640);
//    view.show();

    return app.exec();
}
