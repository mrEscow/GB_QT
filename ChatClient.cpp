#include "ChatClient.h"

const quint16 port = 55555;

ChatClient::ChatClient(QWidget *parent)
    : QWidget(parent)

{
    this->resize(480,640);
    quickWidget = new QQuickWidget(this);
    quickWidget->resize(this->size());
    quickWidget->setClearColor("#e5ecef");
}

ChatClient::~ChatClient()
{

}

void ChatClient::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event)
    quickWidget->resize(this->size());
}


