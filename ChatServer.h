#ifndef CHATSERVER_H
#define CHATSERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QVector>
///#include <QMap>

class ChatServer : public QTcpServer
{
    Q_OBJECT

public:
    ChatServer();
    ~ChatServer();

private slots:
    void incomingConnection(qintptr handle) override;
    void slotReadyRead();

private:
    void sendToClient(QTcpSocket* socket, const QString& msg);
    bool credentials(const QJsonObject& jsObj);
    void serverMessage(const QString& message);

    QTcpSocket* socket;
    QVector<QTcpSocket*> sockets;
    QByteArray byteArray;
    QVector<QPair<QString,QString>> logins;
};

#endif // CHATSERVER_H
