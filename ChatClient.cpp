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
    if(isConnectToChat)
        return true;

    if(login == "" || password == "")
        return false;

    this->login = login;
    this->password = password;

    if(!socket->isValid())
        socket->connectToHost("escow.ru", port);

    if(socket->isValid()){
        qDebug() << "Connect to server!";

        QJsonObject jsObj {
            {"TypeMsg","credentials"},
            {"Who", ""},
            {"Name", login},
            {"Login", login},
            {"Password",password},
            {"Text",""},
            {"Time",""}
        };
        QJsonDocument jsDoc(jsObj);
        QString jsString = QString::fromLatin1(jsDoc.toJson());

        slotToServer(jsString);

        socket->waitForConnected(100);

        return isConnectToChat;

    }
    else{
        qDebug() << "Error! Not connect to server!";
        return false;
    }

    return true;
}

void ChatClient::sendMsg(const QString &text)
{
    QJsonObject jsObj {
        {"TypeMsg","message"},
        {"Who" , "ME"},
        {"Name", login},
        {"Text", text},
        {"Time", ""}
    };
    QJsonDocument jsDoc(jsObj);
    QString jsString = QString::fromLatin1(jsDoc.toJson());

    slotToServer(jsString);
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
    //socket->waitForReadyRead(100);

    QDataStream in(socket);
    in.setVersion(QDataStream::Qt_5_15);
    if(in.status() == QDataStream::Ok){
        QString msg;
        in >> msg;
        //qDebug() << "MSG:" << msg;

        QJsonDocument jsDoc = QJsonDocument::fromJson(msg.toLatin1());
        QJsonObject jsObj = jsDoc.object();
        QString typeMsg = jsObj.value("TypeMsg").toString();

        qDebug() << "TypeMessage:" << typeMsg;

        if(typeMsg == "credentials")
            if(jsObj.value("Text").toString() == "OK"){
                isConnectToChat = true;
                qDebug() << "Credentials: OK!";
                emit conectToChat();
            }
        if(typeMsg == "message"){
            QString who = jsObj.value("Who").toString();
            QString name = jsObj.value("Name").toString();
            QString text = jsObj.value("Text").toString();
            QString time = jsObj.value("Time").toString();
            if(who == "ME" || who == "NotME" || who == "Server"){
                emit messageFromServer(who, name, text, time);
            }
        }
    }
    else {
        qDebug() << "QDataStream error!";
    }

}




