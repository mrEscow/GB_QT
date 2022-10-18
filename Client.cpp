#include "Client.h"

quint16 Client::newUID = 10000;

Client::Client(QTcpSocket *socket)
{
    uid = ++newUID;
    this->socket = socket;
}

QTcpSocket *Client::getSocket() const
{
    return socket;
}

const QString &Client::getName() const
{
    return name;
}

void Client::setName(const QString &newName)
{
    name = newName;
}

const QString &Client::getLogin() const
{
    return login;
}

void Client::setLogin(const QString &newLogin)
{
    login = newLogin;
}

const QString &Client::getPassword() const
{
    return password;
}

void Client::setPassword(const QString &newPassword)
{
    password = newPassword;
}

quint16 Client::getUid() const
{
    return uid;
}
