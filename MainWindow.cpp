#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QFileDialog>
#include <QTextStream>
#include <QDebug>
#include <QKeyEvent>
#include <QTabWidget>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);    
    filterForNameFile = "Текстовый файл(*.txt);";
    connects();
    setSettingsForThisWidgets();
    setSettingsFromParametrs();
}

void MainWindow::connects()
{
    connect(ui->menuCreateNewFile,SIGNAL(triggered(bool)), this, SLOT(runFileCreator()));
    connect(ui->menuCloseFile,SIGNAL(triggered(bool)), this, SLOT(closeFile()));
    connect(ui->menuSave, SIGNAL(triggered(bool)), this, SLOT(saveFile()));
    connect(ui->menuSaveAs, SIGNAL(triggered(bool)), this, SLOT(saveFileAs()));
    connect(ui->menuOpen, SIGNAL(triggered(bool)), this, SLOT(openFileReadWrite()));
    connect(ui->menuOpen_ReadOnly, SIGNAL(triggered(bool)), this, SLOT(openFileReadOnly()));
    connect(ui->menuExit, SIGNAL(triggered(bool)), this, SLOT(exit()));
    connect(ui->toolsParametrs, SIGNAL(triggered(bool)), this, SLOT(parametrs()));
    connect(ui->helpAboutProgramm,SIGNAL(triggered(bool)),this,SLOT(help()));
    connect(&fileCreatorWidget,SIGNAL(newNameFromFileCreator(QString)),this, SLOT(createFile(QString)));
    connect(&parametersWidget, SIGNAL(changeLanguage()),&helpWidget, SLOT(switchLanguage()));
    connect(&parametersWidget, SIGNAL(changeLanguage()),this, SLOT(switchLanguage()));
    connect(&parametersWidget, SIGNAL(changeLanguage()),&fileCreatorWidget, SLOT(switchLanguage()));
    connect(&parametersWidget, SIGNAL(changeShortcuts(QList<Shortcut>)),this, SLOT(changeShortcuts(QList<Shortcut>)));
}

void MainWindow::setSettingsForThisWidgets()
{
    installEventFilter(this);

    ui->textEdit->setEnabled(false);
    ui->menuSave->setEnabled(false);
    ui->menuCloseFile->setEnabled(false);

    ui->splitter->setStretchFactor(0,3);
    ui->splitter->setStretchFactor(1,10);


    ui->tabWidget->setTabText(0,getCorrectName(fileName));
    ui->tabWidget->setTabText(1,"+");
}

void MainWindow::setSettingsFromParametrs()
{
    parametersWidget.setLocalLanguage();

    shortcuts = parametersWidget.getShortcuts();
}

void MainWindow::runFileCreator()
{
    fileCreatorWidget.show();
}

void MainWindow::createFile(QString fileName)
{
    if(!fileName.isEmpty()){
        this->fileName = fileName;
        saveFile();
        ui->tabWidget->setTabText(0,getCorrectName(fileName));
        ui->textEdit->setEnabled(true);
    }

    ui->menuSave->setEnabled(true);
    ui->menuCloseFile->setEnabled(true);
}

void MainWindow::closeFile()
{
    saveFile();
    fileName.clear();
    ui->tabWidget->setTabText(0,getCorrectName(fileName));
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

void MainWindow::saveFileAs()
{
    QString fileNameTemp =
            QFileDialog::getSaveFileName
            (this, tr("Сохранить как..."), QDir::current().path(), filterForNameFile);

    if(!fileName.isEmpty()){
        fileName = fileNameTemp;
        saveFile();
    }
}

void MainWindow::openFileReadWrite()
{
    fileName = QFileDialog::getOpenFileName
            (this, tr("открыть для редактирования"), QDir::current().path(), filterForNameFile);

    openFile(false);
}

void MainWindow::openFileReadOnly()
{
    fileName = QFileDialog::getOpenFileName
            (this, tr("открыть без редактирования"), QDir::current().path(), filterForNameFile);

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
                ui->tabWidget->setTabText(0,getCorrectName(fileName));
                ui->menuSave->setEnabled(true);
                ui->menuCloseFile->setEnabled(true);
                file.close();
            }
        }
    }
}

QString MainWindow::getCorrectName(QString fileName)
{
    if(fileName.isEmpty())
        fileName = "no name";
    else
        for(int count = -1, i = fileName.count(); i > 0 ; i--){
            if(fileName[i] != '/'){
                count++;
                continue;
            }
            fileName.remove(0,fileName.count() - count);
            break;
        }

    return fileName;
}

void MainWindow::exit()
{
    saveFile();
    qApp->exit(0);
}

void MainWindow::parametrs()
{
    parametersWidget.show();
}

void MainWindow::help()
{
    helpWidget.show();
}

void MainWindow::switchLanguage()
{
    this->setWindowTitle(tr("Текстовый редактор"));

    ui->menu->setTitle(tr("Меню"));
    ui->menuCreateNewFile->setText(tr("Создать новый файл"));
    ui->menuCloseFile->setText(tr("Закрыть файл"));
    ui->menuSave->setText(tr("Сохранить"));
    ui->menuSaveAs->setText(tr("Сохранить как..."));
    ui->menuOpen->setText(tr("Открыть"));
    ui->menuOpen_ReadOnly->setText(tr("Открыть для просмотра"));
    ui->menuExit->setText(tr("Выход"));

    ui->tools->setTitle(tr("Инструменты"));
    ui->toolsParametrs->setText(tr("Параметры"));

    ui->help->setTitle(tr("Справка"));
    ui->helpAboutProgramm->setText(tr("О программе"));
}

void MainWindow::changeShortcuts(QList<Shortcut> newShortcuts)
{
    shortcuts = newShortcuts;
}

bool MainWindow::eventFilter(QObject *watched, QEvent *event)
{
    if(watched  == this && event->type() == QEvent::KeyPress){
        auto keyEvent = static_cast<QKeyEvent*>(event);

        for(auto& shortcut: shortcuts){

            if(shortcut.getName()->text() == tr("Открыть"))
                if(keyEvent->key() == shortcut.getKey() && keyEvent->modifiers() == shortcut.getModifier())
                    openFileReadWrite();

            if(shortcut.getName()->text() == tr("Сохранить как"))
                if(keyEvent->key() == shortcut.getKey() && keyEvent->modifiers() == shortcut.getModifier())
                    saveFileAs();

            if(shortcut.getName()->text() == tr("Создать файл"))
                if(keyEvent->key() == shortcut.getKey() && keyEvent->modifiers() == shortcut.getModifier())
                    runFileCreator();

            if(shortcut.getName()->text() == tr("Выход"))
                if(keyEvent->key() == shortcut.getKey() && keyEvent->modifiers() == shortcut.getModifier())
                    exit();
        }
    }

    return QMainWindow::eventFilter(watched,event);
}

MainWindow::~MainWindow()
{
    delete ui;
}
