#ifndef CHATCLIENT_H
#define CHATCLIENT_H

#include <QObject>

class ChatClient : public QObject
{
    Q_OBJECT
public:
    ChatClient(QObject *parent = nullptr);
    ~ChatClient();

};

#endif // CHATCLIENT_H
