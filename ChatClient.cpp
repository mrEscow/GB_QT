#include "ChatClient.h"
#include <QDataStream>

const quint16 port = 55555;

ChatClient::ChatClient(QObject *parent)
    : QObject(parent)
{
    socket = new QTcpSocket(this);
    socket->connectToHost("escow.ru", port);
    connect(socket, SIGNAL(readyRead()), SLOT(slotReadyRead()));
    connect(socket, SIGNAL(disconnected()),socket, SLOT(deleteLater()));
}

ChatClient::~ChatClient()
{
}

bool ChatClient::checkCredentials(const QString &login, const QString &password)
{
    slotToServer("Login:"+login+" "+"Password:"+password);

    if(login == "login" && password == "password")
        return true;

    return false;
}

void ChatClient::slotToServer(const QString &msg)
{
    byteArray.clear();
    QDataStream out(&byteArray, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_15);
    out << msg;
    socket->write(byteArray);
}

void ChatClient::slotReadyRead()
{
    QDataStream in(socket);
    in.setVersion(QDataStream::Qt_5_15);
    if(in.status() == QDataStream::Ok){
        QString msg;
        in >> msg;
        qDebug() << "MSG:" << msg;
    }
    else {
        qDebug() << "QDataStream error!";
    }
}




