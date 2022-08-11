#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QFileDialog>
#include <QTextStream>
#include <QDebug>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //ui->textEdit->setReadOnly(true);
    ui->textEdit->setEnabled(false);

    filter = "Текстовый файл(*.txt);";

    connect(ui->saveButton,SIGNAL(clicked()),this,SLOT(saveFile_as()));
    connect(ui->openButton,SIGNAL(clicked()),this,SLOT(openFile()));
    connect(ui->helpButton,SIGNAL(clicked()),this,SLOT(help()));


    connect(ui->menuCreateNewFile,SIGNAL(triggered(bool)), this, SLOT(createFile()));

    connect(ui->menuSave, SIGNAL(triggered(bool)), this, SLOT(saveFile()));
    connect(ui->menuSave_as, SIGNAL(triggered(bool)), this, SLOT(saveFile_as()));
    connect(ui->menuOpen, SIGNAL(triggered(bool)), this, SLOT(openFile()));
    connect(ui->menuOpen_as, SIGNAL(triggered(bool)), this, SLOT(openFile_as()));

    connect(ui->helpAboutProgramm,SIGNAL(triggered(bool)),this,SLOT(help()));

    connect(&fileCreatorWidget,SIGNAL(newNameFromFileCreator(QString)),this, SLOT(getNamefile(QString)));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createFile()
{
    fileCreatorWidget.show();
//    while(fileCreatorWidget.isEnabled()){
//        system("pause");
//    };

}

void MainWindow::getNamefile(QString fileName)
{
    this->fileName = fileName;
}

void MainWindow::saveFile()
{
    if(!fileName.isEmpty()){
        if (fileName.length() > 0){
            QString ext = QString(&(fileName.data()[fileName.length() - 4]));
            if (ext == ".txt"){
                QFile file(fileName);
                if (file.open(QFile::WriteOnly /* | QFile::NewOnly */)){
                    QTextStream stream(&file);
                    stream << ui->textEdit->toPlainText();
                    file.close();
                }
            }
        }
    }
    else{

        saveFile_as();
    }

}

void MainWindow::saveFile_as()
{
    fileName =
            QFileDialog::getSaveFileName
            (this, tr("Сохранить как"), QDir::current().path(), filter);

    if (fileName.length() > 0){
        QString ext = QString(&(fileName.data()[fileName.length() - 4]));
        if (ext == ".txt"){
            QFile file(fileName);
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
    fileName =
            QFileDialog::getOpenFileName
            (this, tr("открыть для редактирования"), QDir::current().path(), filter);

    if (fileName.length() > 0){
        int index = fileName.indexOf(".txt");
        if (index != -1 && fileName.length() - 4 == index){
            QFile file(fileName);
            if (file.open(QFile::ReadOnly | QFile::ExistingOnly)){
                QTextStream stream(&file);
                ui->textEdit->setPlainText(stream.readAll());
                ui->textEdit->setReadOnly(false);
                file.close();
            }
        }
    }
}

void MainWindow::openFile_as()
{
    fileName =
            QFileDialog::getOpenFileName
            (this, tr("открыть без редактирования"), QDir::current().path(), filter);

    if (fileName.length() > 0){
        int index = fileName.indexOf(".txt");
        if (index != -1 && fileName.length() - 4 == index){
            QFile file(fileName);
            if (file.open(QFile::ReadOnly | QFile::ExistingOnly)){
                QTextStream stream(&file);
                ui->textEdit->setPlainText(stream.readAll());
                ui->textEdit->setReadOnly(true);
                file.close();
            }
        }
    }
}

void MainWindow::exit()
{

}

void MainWindow::parametrs()
{

}

void MainWindow::help()
{
    QFile file(":/HelpText.txt");

    QString helpText;

    if (file.open(QIODevice::ReadOnly)){
        QTextStream stream(&file);
        helpText = stream.readAll();
        file.close();
    }

    qDebug() << helpText;
    helpWidget.setWindowTitle(tr("Справка"));
    helpWidget.setLabelText(tr("Справка"));
    helpWidget.setText(tr(helpText.toStdString().c_str()));
    helpWidget.show();

}

