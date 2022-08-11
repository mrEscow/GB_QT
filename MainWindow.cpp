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
    ui->textEdit->setEnabled(false);
    filter = "Текстовый файл(*.txt);";
    ui->menuSave->setEnabled(false);
    ui->menuCloseFile->setEnabled(false);

    connect(ui->menuCreateNewFile,SIGNAL(triggered(bool)), this, SLOT(runFileCreator()));
    connect(ui->menuCloseFile,SIGNAL(triggered(bool)), this, SLOT(closeFile()));
    connect(ui->menuSave, SIGNAL(triggered(bool)), this, SLOT(saveFile()));
    connect(ui->menuSave_as, SIGNAL(triggered(bool)), this, SLOT(saveFile_as()));
    connect(ui->menuOpen, SIGNAL(triggered(bool)), this, SLOT(openFileReadWrite()));
    connect(ui->menuOpen_ReadOnly, SIGNAL(triggered(bool)), this, SLOT(openFileReadOnly()));
    connect(ui->menuExit, SIGNAL(triggered(bool)), this, SLOT(exit()));

    connect(ui->toolsParametrs, SIGNAL(triggered(bool)), this, SLOT(parametrs()));

    connect(ui->helpAboutProgramm,SIGNAL(triggered(bool)),this,SLOT(help()));

    connect(&fileCreatorWidget,SIGNAL(newNameFromFileCreator(QString)),this, SLOT(createFile(QString)));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::runFileCreator()
{
    this->setEnabled(false);
    fileCreatorWidget.show();
}

void MainWindow::createFile(QString fileName)
{
    if(!fileName.isEmpty()){
        this->fileName = fileName;
        saveFile();
        ui->nameFileLabel->setText(fileName);
        ui->textEdit->setEnabled(true);
    }

    this->setEnabled(true);
    ui->menuSave->setEnabled(true);
    ui->menuCloseFile->setEnabled(true);
}

void MainWindow::closeFile()
{
    saveFile();
    fileName.clear();
    ui->nameFileLabel->clear();
    ui->textEdit->clear();
    ui->textEdit->setEnabled(false);
    ui->menuSave->setEnabled(false);
    ui->menuCloseFile->setEnabled(false);
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
}

void MainWindow::saveFile_as()
{
    QString fileNameTemp =
            QFileDialog::getSaveFileName
            (this, tr("Сохранить как"), QDir::current().path(), filter);

    if (fileNameTemp.length() > 0){
        QString ext = QString(&(fileNameTemp.data()[fileNameTemp.length() - 4]));
        if (ext == ".txt"){
            QFile file(fileNameTemp);
            if (file.open(QFile::WriteOnly /* | QFile::NewOnly */)){
                QTextStream stream(&file);
                stream << ui->textEdit->toPlainText();
                fileName = fileNameTemp;
                file.close();
            }
        }
    }
}

void MainWindow::openFileReadWrite()
{
    fileName = QFileDialog::getOpenFileName
            (this, tr("открыть для редактирования"), QDir::current().path(), filter);

    openFile(false);
}

void MainWindow::openFileReadOnly()
{
    fileName = QFileDialog::getOpenFileName
            (this, tr("открыть без редактирования"), QDir::current().path(), filter);

    openFile(true);
}

void MainWindow::openFile(bool isReadOnly)
{
    if (fileName.length() > 0){
        int index = fileName.indexOf(".txt");
        if (index != -1 && fileName.length() - 4 == index){
            QFile file(fileName);
            if (file.open(QFile::ReadOnly | QFile::ExistingOnly)){
                QTextStream stream(&file);
                ui->textEdit->setPlainText(stream.readAll());
                ui->textEdit->setEnabled(true);
                ui->textEdit->setReadOnly(isReadOnly);
                ui->nameFileLabel->setText(fileName);
                ui->menuSave->setEnabled(true);
                ui->menuCloseFile->setEnabled(true);
                file.close();
            }
        }
    }
}

void MainWindow::exit()
{
    saveFile();
    qApp->exit(0);
}

void MainWindow::parametrs()
{
    qDebug() << "PARAMETRS";
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

