#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QDebug>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , _ui(new Ui::MainWindow)
{
    _ui->setupUi(this);

    _model = new QStringListModel(this);
    _ui->_chatListView->setModel(_model);

    connect(_ui->_sendMsgPushButton, SIGNAL(clicked()), SLOT(onSendButton()));
}

MainWindow::~MainWindow()
{
    delete _ui;
}

void MainWindow::onSendButton()
{
    qDebug() << "MainWindow::onSendButton()";

    QString msg;
    msg += _ui->_nikelLineEdit->text();
    msg += ":\n\t";
    msg += _ui->_inputTextLineEdit->text();

    list << msg;

    _model->setStringList(list);
}

