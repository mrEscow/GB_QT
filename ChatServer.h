#ifndef CHATSERVER_H
#define CHATSERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QVector>

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
    void sendToClients(const QString& msg);

    QTcpSocket* socket;
    QVector<QTcpSocket*> sockets;
    QByteArray byteArray;
};

#endif // CHATSERVER_H
