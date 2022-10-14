#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QDateTime>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_ui(new Ui::MainWindow)
{
    m_ui->setupUi(this);

    connect(m_ui->_sendMsgPushButton, SIGNAL(clicked()), SLOT(onSendButton()));
}

MainWindow::~MainWindow()
{
    delete m_ui;
}

void MainWindow::onSendButton()
{
    if(m_ui->_nikelLineEdit->text().isEmpty() || m_ui->textEdit->toPlainText().isEmpty())
        return;

    QString nikeName = m_ui->_nikelLineEdit->text();
    QString msg = nikeName + ":\n" + m_ui->textEdit->toPlainText();
    m_ui->textEdit->setText("");
    QString time = QString::number(QDateTime::currentDateTime().toTime_t()); // Отметка времени

    bool isSending = true; // отправка

    qDebug()<<"addMessage" << msg << time << m_ui->_chatListWidget->count();
    if(m_ui->_chatListWidget->count() % 2) {
        if(isSending) {
            dealMessageTime(time);

            ChatMsg* messageW = new ChatMsg(m_ui->_chatListWidget->parentWidget());
            QListWidgetItem* item = new QListWidgetItem(m_ui->_chatListWidget);
            dealMessage(messageW, item, msg, time, ChatMsg::User_Me);
        } else {
            bool isOver = true;
            for(int i = m_ui->_chatListWidget->count() - 1; i > 0; i--) {
                ChatMsg* messageW = (ChatMsg*)m_ui->_chatListWidget->itemWidget(m_ui->_chatListWidget->item(i));
                if(messageW->text() == msg) {
                    isOver = false;
                    messageW->setTextSuccess();
                }
            }
            if(isOver) {
                dealMessageTime(time);

                ChatMsg* messageW = new ChatMsg(m_ui->_chatListWidget->parentWidget());
                QListWidgetItem* item = new QListWidgetItem(m_ui->_chatListWidget);
                dealMessage(messageW, item, msg, time, ChatMsg::User_Me);
                messageW->setTextSuccess();
            }
        }
    } else {
        if(msg != "") {
            dealMessageTime(time);

            ChatMsg* messageW = new ChatMsg(m_ui->_chatListWidget->parentWidget());
            QListWidgetItem* item = new QListWidgetItem(m_ui->_chatListWidget);
            dealMessage(messageW, item, msg, time, ChatMsg::User_She);
        }
    }
    m_ui->_chatListWidget->setCurrentRow(m_ui->_chatListWidget->count() - 1);
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


//    m_ui->textEdit->resize(this->width() - 20, this->height() - 20);
//    //m_ui->textEdit->move(10, 10);

//    m_ui->_sendMsgPushButton->move(m_ui->textEdit->width()+m_ui->textEdit->x() - m_ui->_sendMsgPushButton->width() - 10,
//                         m_ui->textEdit->height()+m_ui->textEdit->y() - m_ui->_sendMsgPushButton->height() - 10);


    for(int i = 0; i < m_ui->_chatListWidget->count(); i++) {
        ChatMsg* messageW = (ChatMsg*)m_ui->_chatListWidget->itemWidget(m_ui->_chatListWidget->item(i));
        QListWidgetItem* item = m_ui->_chatListWidget->item(i);

        dealMessage(messageW, item, messageW->text(), messageW->time(), messageW->userType());
    }
}
