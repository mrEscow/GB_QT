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
    Q_INVOKABLE void sendMsg(const QString& text);
signals:
    Q_INVOKABLE void messageFromServer(const QString& who, const QString& name, const QString& text, const QString& time);
    Q_INVOKABLE void conectToChat();
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
