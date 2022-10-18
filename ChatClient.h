#ifndef CHATCLIENT_H
#define CHATCLIENT_H

#include <QObject>
#include <QTcpSocket>

class ChatClient : public QObject
{
    Q_OBJECT
public:
    ChatClient(QObject *parent = nullptr);
    ~ChatClient();
    Q_INVOKABLE bool checkCredentials(const QString& login, const QString& password);
private slots:
    void slotToServer(const QString& msg);
    void slotReadyRead();
private:
    QString login;
    QString password;
    bool isConnectToChat;
    QTcpSocket *socket;
    QByteArray byteArray;
};

#endif // CHATCLIENT_H
