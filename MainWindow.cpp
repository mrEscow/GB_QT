#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QTextEdit>
#include <QLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    checkText = new CheckText(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_textEdit_textChanged()
{

    textFromEditor = ui->textEdit->toPlainText();
    textOld = textFromEditor;

    checkText->changeText(textFromEditor);

    if(textOld != textFromEditor){
        ui->textEdit->setText(textFromEditor);

        QTextCursor cursor = ui->textEdit->textCursor();
        cursor.movePosition(QTextCursor::End);
        ui->textEdit->setTextCursor(cursor);
    }
}

