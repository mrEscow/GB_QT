#ifndef CHATSERVER_H
#define CHATSERVER_H

#include "Client.h"
#include <QTcpServer>
#include <QTcpSocket>
#include <QVector>


class ChatServer : public QTcpServer
{
    Q_OBJECT
private:
    struct MSG{
        QString TypeMsg;
        QString Who;
        QString Name;
        QString Text;
        QString Time;
    };

public:
    ChatServer();
    ~ChatServer();

private slots:
    void incomingConnection(qintptr handle) override;
    void slotReadyRead();
    void slotStateChange(QAbstractSocket::SocketState stage);

private:
    void sendToClient(QTcpSocket* socket, const QString& msg);
    void sendToClient(QTcpSocket* socket, const MSG& msg);
    bool credentials(const QJsonObject& jsObj);
    void serverMessage(const QString& message);

    QTcpSocket* socket;
    //QVector<QTcpSocket*> sockets;
    QVector<Client> clients;
    QByteArray byteArray;
    QVector<QPair<QString, QString>> logins;
    QVector<MSG> stackMessanges;
};

#endif // CHATSERVER_H
