#ifndef CLIENT_H
#define CLIENT_H

#include <QTcpSocket>
//#include <QObject>

class Client
{
public:
    Client(QTcpSocket* socket);
    QTcpSocket *getSocket() const;

    const QString &getName() const;
    void setName(const QString &newName);

    const QString &getLogin() const;
    void setLogin(const QString &newLogin);

    const QString &getPassword() const;
    void setPassword(const QString &newPassword);

    quint16 getUid() const;

private:
    static quint16 newUID;
    quint16 uid;
    QString name;
    QString login;
    QString password;
    QTcpSocket* socket;
};

#endif // CLIENT_H
