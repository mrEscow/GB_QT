#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QDateTime>
#include <QDebug>

const quint16 port = 20000;



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_ui(new Ui::MainWindow)
{
    m_ui->setupUi(this);
    m_soket = new QUdpSocket(this);
    m_soket->bind(QHostAddress::Any, port);

    connect(m_soket, SIGNAL(readyRead()), SLOT(readFromSocket()));
    connect(m_ui->_sendMsgPushButton, SIGNAL(clicked()), SLOT(onSendButton()));
}

MainWindow::~MainWindow()
{
    delete m_ui;
}

// private slots:
void MainWindow::readFromSocket()
{
    QByteArray datagram;
    datagram.resize(m_soket->pendingDatagramSize());
    QHostAddress *address = new QHostAddress();
    m_soket->readDatagram(datagram.data(), datagram.size(), address);

    qDebug() << "ReadFromSocket(): " << datagram;

    QDataStream in(&datagram, QIODevice::ReadOnly);

    qint64 size = -1;
    if(in.device()->size() > sizeof(qint64)) {
        in >> size;
    } else return;
    if (in.device()->size() - sizeof(qint64) < size) return;

    qint8 type = 0;
    in >> type;

    if (type == qint8(TYPE_MSG::USUAL_MESSAGE)) {
        QString str;
        in >> str;
        qDebug() << str;
        if(sendingMgs != str){
            QString time = QString::number(QDateTime::currentDateTime().toTime_t()); // Отметка времени
            dealMessageTime(time);
            ChatMsg* messageW = new ChatMsg(m_ui->_chatListWidget->parentWidget());
            QListWidgetItem* item = new QListWidgetItem(m_ui->_chatListWidget);
            dealMessage(messageW, item, str, time, ChatMsg::User_She);
        }
        //else
            //sendMsg.clean();

    } else if (type == qint8(TYPE_MSG::PERSON_ONLINE)) {
        // Добавление пользователя с считанным QHostAddress //
    } else if (type == qint8(TYPE_MSG::WHO_IS_ONLINE)) {
        send(nickName, qint8(TYPE_MSG::PERSON_ONLINE));
    }
}

// private slots:
void MainWindow::onSendButton()
{
    if(m_ui->_nikelLineEdit->text().isEmpty() || m_ui->textEdit->toPlainText().isEmpty())
        return;

    nickName = m_ui->_nikelLineEdit->text();
    QString text = m_ui->textEdit->toPlainText();
    QString msg = nickName + ":\n" + text;
    sendingMgs = msg;
    m_ui->textEdit->setText("");
    QString time = QString::number(QDateTime::currentDateTime().toTime_t()); // Отметка времени

    dealMessageTime(time);
    ChatMsg* messageW = new ChatMsg(m_ui->_chatListWidget->parentWidget());
    QListWidgetItem* item = new QListWidgetItem(m_ui->_chatListWidget);
    dealMessage(messageW, item, msg, time, ChatMsg::User_Me);

    m_ui->_chatListWidget->setCurrentRow(m_ui->_chatListWidget->count() - 1);

    send(msg, qint8(TYPE_MSG::USUAL_MESSAGE));
}

void MainWindow::send(QString str, qint8 type)
{
    QByteArray data;
    QDataStream out(&data, QIODevice::WriteOnly);
    out << qint64(0);
    out << qint8(type);
    out << str;
    out.device()->seek(qint64(0));
    out << qint64(data.size() - sizeof(qint64));
    m_soket->writeDatagram(data, QHostAddress::Broadcast, port);
}

void MainWindow::dealMessage(ChatMsg *messageW, QListWidgetItem *item, QString text, QString time,  ChatMsg::User_Type type)
{
    messageW->setFixedWidth(this->width());
    QSize size = messageW->fontRect(text);
    item->setSizeHint(size);
    messageW->setText(text, time, size, type);
    m_ui->_chatListWidget->setItemWidget(item, messageW);
}

void MainWindow::dealMessageTime(QString curMsgTime)
{
    bool isShowTime = false;
    if(m_ui->_chatListWidget->count() > 0) {
        QListWidgetItem* lastItem = m_ui->_chatListWidget->item(m_ui->_chatListWidget->count() - 1);
        ChatMsg* messageW = (ChatMsg*)m_ui->_chatListWidget->itemWidget(lastItem);
        int lastTime = messageW->time().toInt();
        int curTime = curMsgTime.toInt();
        qDebug() << "curTime lastTime:" << curTime - lastTime;
        isShowTime = ((curTime-lastTime) > 60); // Разница между двумя сообщениями составляет одну минуту
        //        isShowTime = true;
    } else {
        isShowTime = true;
    }

    if(isShowTime) {
        ChatMsg* messageTime = new ChatMsg(m_ui->_chatListWidget->parentWidget());
        QListWidgetItem* itemTime = new QListWidgetItem(m_ui->_chatListWidget);

        QSize size = QSize(this->width(), 40);
        messageTime->resize(size);
        itemTime->setSizeHint(size);
        messageTime->setText(curMsgTime, curMsgTime, size, ChatMsg::User_Time);
        m_ui->_chatListWidget->setItemWidget(itemTime, messageTime);
    }
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);

    for(int i = 0; i < m_ui->_chatListWidget->count(); i++) {
        ChatMsg* messageW = (ChatMsg*)m_ui->_chatListWidget->itemWidget(m_ui->_chatListWidget->item(i));
        QListWidgetItem* item = m_ui->_chatListWidget->item(i);

        dealMessage(messageW, item, messageW->text(), messageW->time(), messageW->userType());
    }
}


