#include "ChatServer.h"
#include <QDataStream>
#include <QJsonDocument>
#include <QJsonObject>
#include <QTime>

const quint16 port = 55555;

ChatServer::ChatServer()
{
    if(this->listen(QHostAddress::Any, port))
        qDebug() << "Start listen!";
    else{
        qDebug() << "Error listen!";
        close();
    }
}

ChatServer::~ChatServer()
{

}

void ChatServer::incomingConnection(qintptr handle)
{
    socket = new QTcpSocket;
    socket->setSocketDescriptor(handle);
    connect(socket, SIGNAL(readyRead()), SLOT(slotReadyRead()));    
    connect(socket, SIGNAL(stateChanged(QAbstractSocket::SocketState)),SLOT(slotStateChange(QAbstractSocket::SocketState)));
    connect(socket, SIGNAL(disconnected()), socket, SLOT(deleteLater()));

    Client newClient(socket);

    clients.push_back(newClient);

    qDebug() << "Client connectd! ID:" << newClient.getUid() << "Handel:" << handle;
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
        qDebug() << "TypeMessege:" << typeMsg;

        if(typeMsg == "credentials"){
            qDebug() << "NewClient: { "
                     << "Name:" << jsObj.value("login").toString()
                     << "}";

            if(credentials(jsObj)){
                for(auto& client: clients)
                    if(client.getSocket() == socket){
                        client.setName(jsObj.value("login").toString());
                        client.setLogin(jsObj.value("password").toString());
                        client.setPassword(jsObj.value("login").toString());
                    }

                jsObj.insert("msg","OK");
                jsDoc.setObject(jsObj);
                msg = QString::fromLatin1(jsDoc.toJson());

                sendToClient(socket,msg);

                socket->waitForReadyRead(500);

                serverMessage("Добро пожаловать " + jsObj.value("login").toString() + "!");
            }
            return;
        }

        if(typeMsg == "message"){
            qDebug() << "Client: { "
                     << "Name:" << jsObj.value("login").toString()
                     << "Text:" << jsObj.value("msg").toString()
                     << "Time:" << QTime::currentTime().toString() << "}";

            jsObj.insert("time",QTime::currentTime().toString());
            jsDoc.setObject(jsObj);
            msg = QString::fromLatin1(jsDoc.toJson());
            qDebug() << "Send this msg for this client";
            sendToClient(socket, msg);

            jsObj.insert("who","NotME");
            jsDoc.setObject(jsObj);
            msg = QString::fromLatin1(jsDoc.toJson());
            qDebug() << "Send this msg for all clients";
            for(auto& client: clients)
                if(client.getSocket()->isValid() && client.getSocket() != socket)
                    sendToClient(client.getSocket(),msg);
        }
    }
    else
        qDebug() << "DataStream error!";

}

void ChatServer::slotStateChange(QAbstractSocket::SocketState stage)
{
    if(stage == QAbstractSocket::UnconnectedState){
        QTcpSocket* socket = qobject_cast<QTcpSocket*>(sender());
        QMutableVectorIterator mutableVec(clients);
        QString name;

        while(mutableVec.hasNext()){
            if(mutableVec.next().getSocket() == socket){
                name = mutableVec.value().getName();
                mutableVec.remove();
            }
        }
        serverMessage("Чат покинул " + name + "!");
    }
}

void ChatServer::sendToClient(QTcpSocket* socket, const QString &msg)
{
    byteArray.clear();
    QDataStream out(&byteArray, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_15);
    out << msg;
    socket->write(byteArray);
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

void ChatServer::serverMessage(const QString &message)
{
    qDebug() << "Send message for all:" << message;

    QJsonObject jsObjHello {
        {"typeMsg", "message"},
        {"login", "Server"},
        {"who", "Server"},
        {"msg", message},
        {"time", QTime::currentTime().toString()}
    };
    QJsonDocument jsDoc(jsObjHello);
    QString msg = QString::fromLatin1(jsDoc.toJson());

    for(auto& client: clients)
        if(client.getSocket()->isValid())
            sendToClient(client.getSocket(), msg);
}
