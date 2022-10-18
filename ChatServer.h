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

// QTcpServer interface
private slots:
    void incomingConnection(qintptr handle) override;
    void slotReadyRead();

private:
    void sendToClient(QTcpSocket* socket, const QString& msg);
    void sendToClients(const QString& msg);
    bool credentials(const QJsonObject& jsObj);

    QTcpSocket* socket;
    QVector<QTcpSocket*> sockets;
    QByteArray byteArray;
    QVector<QPair<QString,QString>> logins;
};

#endif // CHATSERVER_H
