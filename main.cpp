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

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterType<ChatClient>("EscowCompany", 1, 0, "ChatClient");

    QQuickView view;
    view.setResizeMode(QQuickView::SizeRootObjectToView);
    view.setSource(QUrl(QStringLiteral("qrc:/main.qml")));
    view.resize(480,640);
    view.show();

    return app.exec();
}
