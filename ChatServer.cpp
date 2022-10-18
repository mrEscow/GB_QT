#include "ChatServer.h"
#include <QDataStream>
#include <QJsonDocument>
#include <QJsonObject>

const quint16 port = 55555;

ChatServer::ChatServer()
{
    if(this->listen(QHostAddress::Any, port))
        qDebug() << "Start listen!";
    else
        qDebug() << "Error listen!";
}

ChatServer::~ChatServer()
{

}

void ChatServer::incomingConnection(qintptr handle)
{
    socket = new QTcpSocket;
    socket->setSocketDescriptor(handle);
    connect(socket, SIGNAL(readyRead()), SLOT(slotReadyRead()));
    connect(socket, SIGNAL(disconnected()), socket, SLOT(deleteLater()));

    sockets.push_back(socket);
    qDebug() << "Client connectd" << handle;
}

void ChatServer::slotReadyRead()
{
    socket = qobject_cast<QTcpSocket*>(sender());
    QDataStream in(socket);
    in.setVersion(QDataStream::Qt_5_15);
    if(in.status() == QDataStream::Ok){
        qDebug() << "read...";
        QString msg;
        in >> msg;

        QJsonDocument jsDoc = QJsonDocument::fromJson(msg.toLatin1());
        QJsonObject jsObj = jsDoc.object();
        QString typeMsg = jsObj.value("typeMsg").toString();

        qDebug() << "TypeMassege:" << typeMsg;
        if(typeMsg == "credentials")
            if(credentials(jsObj)){
                jsObj.insert("msg","OK");
                jsDoc.setObject(jsObj);
                msg = QString::fromLatin1(jsDoc.toJson());
                sendToClient(socket,msg);
            }

        sendToClients(msg);
    }
    else
        qDebug() << "DataStream error!";

}

void ChatServer::sendToClient(QTcpSocket* socket, const QString &msg)
{
    byteArray.clear();
    QDataStream out(&byteArray, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_15);
    out << msg;
    socket->write(byteArray);
}

void ChatServer::sendToClients(const QString &msg)
{
    byteArray.clear();
    QDataStream out(&byteArray, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_15);
    out << msg;
    for(auto& client:sockets)
        if(client->isValid())
            client->write(byteArray);
}

bool ChatServer::credentials(const QJsonObject &jsObj)
{
    QString login = jsObj.value("login").toString();
    QString password = jsObj.value("password").toString();

    QPair pair{login,password};
    if(logins.contains(pair)){
        qDebug() << "Credentials OK";
        return true;
    }
    else{
        qDebug() << "Credentials BED push new client!";
        return true;
    }

    return false;
}
