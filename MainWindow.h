#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
//#include <QStandardItemModel>
//#include <QItemDelegate>
#include <QListWidgetItem>
#include "ChatMsg.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void dealMessage(ChatMsg *messageW, QListWidgetItem *item, QString text, QString time, ChatMsg::User_Type type);
    void dealMessageTime(QString curMsgTime);
protected:
    void resizeEvent(QResizeEvent *event);

private slots:
    void onSendButton();

private:
    Ui::MainWindow* m_ui;
};

#endif // MAINWINDOW_H
