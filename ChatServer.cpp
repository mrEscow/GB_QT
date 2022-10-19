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
    qDebug() << "================================================";
    qDebug() << "New client connectd! ID:" << newClient.getUid() << "Handel:" << handle;
}

void ChatServer::slotReadyRead()
{
    socket = qobject_cast<QTcpSocket*>(sender());
    QDataStream in(socket);
    in.setVersion(QDataStream::Qt_5_15);
    if(in.status() == QDataStream::Ok){
        //qDebug() << "read...";
        QString msg;
        in >> msg;

        QJsonDocument jsDoc = QJsonDocument::fromJson(msg.toLatin1());
        QJsonObject jsObj = jsDoc.object();

        QString typeMsg = jsObj.value("TypeMsg").toString();
        qDebug() << "TypeMessege:" << typeMsg;

        if(typeMsg == "credentials"){
            qDebug() << "NewClient: { "
                     << "Name:" << jsObj.value("Name").toString()
                     << "}";

            if(credentials(jsObj)){
                for(auto& client: clients)
                    if(client.getSocket() == socket){
                        client.setName(jsObj.value("Name").toString());
                        client.setLogin(jsObj.value("Login").toString());
                        client.setPassword(jsObj.value("Password").toString());
                    }

                jsObj.insert("Text","OK");
                jsDoc.setObject(jsObj);
                msg = QString::fromLatin1(jsDoc.toJson());

                sendToClient(socket,msg);

                socket->waitForReadyRead(500);

                QVectorIterator iterator(stackMessanges);
                iterator.toBack();
                quint8 countOldMassege = 0;
                while(iterator.hasPrevious() && countOldMassege++ != 10)
                    sendToClient(socket,iterator.previous());

                serverMessage("Добро пожаловать " + jsObj.value("Name").toString() + "!");
                qDebug() << "================================================";
            }
            return;
        }

        if(typeMsg == "message"){

            qDebug() << "Client: { "
                     << "Name:" << jsObj.value("Name").toString()
                     << "Text:" << jsObj.value("Text").toString()
                     << "Time:" << QTime::currentTime().toString() << "}";

            jsObj.insert("Time", QTime::currentTime().toString());
            jsDoc.setObject(jsObj);
            msg = QString::fromLatin1(jsDoc.toJson());
            qDebug() << "Send this msg for this client";
            sendToClient(socket, msg);

            jsObj.insert("Who","NotME");
            jsDoc.setObject(jsObj);
            msg = QString::fromLatin1(jsDoc.toJson());
            qDebug() << "Send this msg for all clients";
            for(auto& client: clients)
                if(client.getSocket()->isValid() && client.getSocket() != socket)
                    sendToClient(client.getSocket(),msg);

            stackMessanges.push_back({
                jsObj.value("TypeMsg").toString(),
                jsObj.value("Who").toString(),
                jsObj.value("Name").toString(),
                jsObj.value("Text").toString(),
                jsObj.value("Time").toString()
            });
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

void ChatServer::sendToClient(QTcpSocket *socket, const MSG &msg)
{
    QJsonObject jsObj{
        {"TypeMsg", msg.TypeMsg},
        {"Who", msg.Who},
        {"Name", msg.Name},
        {"Text", msg.Text},
        {"Time", msg.Time}
    };
    QJsonDocument jsDoc(jsObj);

    QString jsSrting = QString::fromLatin1(jsDoc.toJson());

    byteArray.clear();
    QDataStream out(&byteArray, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_15);
    out << jsSrting;

    socket->waitForReadyRead(100);
    socket->write(byteArray);
    socket->waitForReadyRead(100);
}

bool ChatServer::credentials(const QJsonObject &jsObj)
{
    QString login = jsObj.value("Login").toString();
    QString password = jsObj.value("Password").toString();

    QPair pair{login, password};
    if(logins.contains(pair)){
        qDebug() << "Credentials OK";
        return true;
    }
    else{
        qDebug() << "Credentials BED push new client!";
        logins.push_back(pair);
        return true;
    }

    return false;
}

void ChatServer::serverMessage(const QString &message)
{
    qDebug() << "Send message for all:" << message;

    QJsonObject jsObjHello {
        {"TypeMsg", "message"},
        {"Who", "Server"},
        {"Name", "Server"},
        {"Text", message},
        {"Time", QTime::currentTime().toString()}
    };
    QJsonDocument jsDoc(jsObjHello);
    QString msg = QString::fromLatin1(jsDoc.toJson());

    for(auto& client: clients)
        if(client.getSocket()->isValid())
            sendToClient(client.getSocket(), msg);
}
