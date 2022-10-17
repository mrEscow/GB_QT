#ifndef CHATCLIENT_H
#define CHATCLIENT_H

#include <QWidget>
#include <QQuickWidget>

class ChatClient : public QWidget
{
    Q_OBJECT

public:
    ChatClient(QWidget *parent = nullptr);
    ~ChatClient();


private slots:

protected:
    void resizeEvent(QResizeEvent *event);

private:
    QQuickWidget* quickWidget;


};

#endif // CHATCLIENT_H
