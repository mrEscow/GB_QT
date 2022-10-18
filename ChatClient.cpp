#include "ChatClient.h"
#include <QDataStream>
#include <QJsonObject>
#include <QJsonDocument>

const quint16 port = 55555;

ChatClient::ChatClient(QObject *parent)
    : QObject(parent)
{
    isConnectToChat = false;
    socket = new QTcpSocket(this);

    connect(socket, SIGNAL(readyRead()), SLOT(slotReadyRead()));
    connect(socket, SIGNAL(disconnected()), socket, SLOT(deleteLater()));
}

ChatClient::~ChatClient()
{
}

bool ChatClient::checkCredentials(const QString &login, const QString &password)
{
    if(login == "" && password == "")
        return false;

    if(!socket->isValid())
        socket->connectToHost("escow.ru", port);

    if(socket->isValid()){
        qDebug() << "Connect to server!";

        QJsonObject jsObj {
            {"typeMsg","credentials"},
            {"id",-1},
            {"login", login},
            {"password",password},
            {"msg",""}
        };
        QJsonDocument jsDoc(jsObj);
        QString jsString = QString::fromLatin1(jsDoc.toJson());

        slotToServer(jsString);
        while(socket->waitForReadyRead(200)){}

        return isConnectToChat;

    }
    else{
        qDebug() << "Error! Not connect to server!";
        return false;
    }

    return true;
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
        //qDebug() << "MSG:" << msg;

        QJsonDocument jsDoc = QJsonDocument::fromJson(msg.toLatin1());
        QJsonObject jsObj = jsDoc.object();
        QString typeMsg = jsObj.value("typeMsg").toString();

        qDebug() << "TypeMassege:" << typeMsg;
        if(typeMsg == "credentials")
            if(jsObj.value("msg").toString() == "OK"){
                isConnectToChat = true;
                 qDebug() << "Credentials: OK!";
            }
    }
    else {
        qDebug() << "QDataStream error!";
    }
}




