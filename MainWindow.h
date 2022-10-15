#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QUdpSocket>
#include <QListWidgetItem>
#include "ChatMsg.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
    enum class TYPE_MSG : qint8
    {
        USUAL_MESSAGE = 1,
        PERSON_ONLINE = 2,
        WHO_IS_ONLINE = 3
    };

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void dealMessage(ChatMsg *messageW, QListWidgetItem *item, QString text, QString time, ChatMsg::User_Type type);
    void dealMessageTime(QString curMsgTime);
protected:
    void resizeEvent(QResizeEvent *event);

private slots:
    void readFromSocket();
    void onSendButton();
    void send(QString str, qint8 type);

private:
    Ui::MainWindow* m_ui;
    QString nickName;
    QUdpSocket* m_soket;
    QString sendingMgs;
};

#endif // MAINWINDOW_H
