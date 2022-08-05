#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->saveButton,SIGNAL(clicked()),this,SLOT(saveFile()));
    connect(ui->openButton,SIGNAL(clicked()),this,SLOT(openFile()));

    filter = "Текстовый файл(*.txt);";

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::saveFile()
{
    QString filename =
            QFileDialog::getSaveFileName
            (this, "СОХРАНЕНИЕ ФАЙЛА", QDir::current().path(), filter);

    if (filename.length() > 0){
        QString ext = QString(&(filename.data()[filename.length() - 4]));
        if (ext == ".txt"){
            QFile file(filename);
            if (file.open(QFile::WriteOnly /* | QFile::NewOnly */)){
                QTextStream stream(&file);
                stream << ui->textEdit->toPlainText();
                file.close();
            }
        }
    }
}

void MainWindow::openFile()
{
    QString filename =
            QFileDialog::getOpenFileName
            (this, "ОТКРЫТИЕ ФАЙЛА", QDir::current().path(), filter);

    if (filename.length() > 0){
        int index = filename.indexOf(".txt");
        if (index != -1 && filename.length() - 4 == index){
            QFile file(filename);
            if (file.open(QFile::ReadOnly | QFile::ExistingOnly)){
                QTextStream stream(&file);
                ui->textEdit->setPlainText(stream.readAll());
                file.close();
            }
        }
    }
}

