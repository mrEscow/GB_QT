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
    setSettingsForThisWidgets();
    setSettingsFromParametrs();
}

void MainWindow::setSettingsForThisWidgets()
{
    installEventFilter(this);

    //ui->textEdit->setEnabled(false);
    ui->menuSave->setEnabled(false);
    ui->menuCloseFile->setEnabled(false);

    filterForNameFile = "Текстовый файл(*.txt);";

    fileSystemViwer = new FileSystemViewer(
                ui->pushButtonHome,
                ui->pushButtonUp,
                ui->pushButtonSearch,
                ui->lineEditNavigation,
                ui->listView
                );

    fileSystemViwer->setHomePath(QDir::current().path());
    fileSystemViwer->setRootPathAndIndex(QDir::current().path());

    ui->splitter->setStretchFactor(0,3);
    ui->splitter->setStretchFactor(1,15);

    //openFiles
    ui->tabWidget->removeTab(1);
    //ui->tabWidget->setTabText(0,getCorrectName(fileName));
    ui->tabWidget->setTabText(0,"+");

    //textEditorsList.push_back(ui->textEdit);

    connects();
}

void MainWindow::connects()
{
    connect(ui->menuCreateNewFile, SIGNAL(triggered(bool)), this, SLOT(runFileCreator()));
    connect(ui->menuCloseFile, SIGNAL(triggered(bool)), this, SLOT(closeFile()));
    connect(ui->menuSave, SIGNAL(triggered(bool)), this, SLOT(saveFile()));
    connect(ui->menuSaveAs, SIGNAL(triggered(bool)), this, SLOT(saveFileAs()));
    connect(ui->menuOpen, SIGNAL(triggered(bool)), this, SLOT(openFileReadWrite()));
    connect(ui->menuOpen_ReadOnly, SIGNAL(triggered(bool)), this, SLOT(openFileReadOnly()));
    connect(ui->menuExit, SIGNAL(triggered(bool)), this, SLOT(exit()));
    connect(ui->toolsParametrs, SIGNAL(triggered(bool)), this, SLOT(parametrs()));
    connect(ui->helpAboutProgramm, SIGNAL(triggered(bool)),this, SLOT(help()));

    connect(&fileCreatorWidget, SIGNAL(newNameFromFileCreator(QString)), this, SLOT(createFile(QString)));

    connect(&parametersWidget, SIGNAL(changeLanguage()), &helpWidget, SLOT(switchLanguage()));
    connect(&parametersWidget, SIGNAL(changeLanguage()), this, SLOT(switchLanguage()));
    connect(&parametersWidget, SIGNAL(changeLanguage()), &fileCreatorWidget, SLOT(switchLanguage()));
    connect(&parametersWidget, SIGNAL(changeShortcuts(QList<Shortcut>)), this, SLOT(changeShortcuts(QList<Shortcut>)));

    connect(fileSystemViwer, SIGNAL(openFile(QString,bool)), this, SLOT(openFile(QString,bool)));

    connect(ui->tabWidget, SIGNAL(tabBarClicked(int)),this, SLOT(addTab(int)));
    connect(ui->tabWidget, SIGNAL(currentChanged(int)),this, SLOT(addTab(int)));
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
        QTextEdit* textEdit = new QTextEdit;
        senderTextEdit = textEdit;
        OpenFile openFile(getCorrectName(fileName),fileSystemViwer->getCurrentPath(),textEdit);
        openFiles.append(openFile);
        ui->tabWidget->insertTab(0,textEdit,openFile.getName());
        ui->tabWidget->setCurrentIndex(0);
        saveFile();
    }

    ui->menuSave->setEnabled(true);
    ui->menuCloseFile->setEnabled(true);
}

void MainWindow::closeFile()
{
//    QMutableListIterator  it(openFiles);

//    for(auto& oF: openFiles){
//        if(oF.getTextEdit() == senderTextEdit){
//            qDebug() << "TRUE!!!";
//        }
//    }

//    while(it.hasNext()){
//        qDebug() << "qqqqq";
//        OpenFile currentValue = it.next();
//        qDebug() << currentValue.getTextEdit()->toPlainText();
//        qDebug() << senderTextEdit->toPlainText();
//        if(currentValue.getTextEdit() == senderTextEdit){
//          qDebug() << "TTTTT";
//          it.remove();
//        }
//    }


    //ui->tabWidget->removeTab(ui->tabWidget->currentIndex());

    if(openFiles.isEmpty()){
        ui->menuSave->setEnabled(false);
        ui->menuCloseFile->setEnabled(false);
    }
}

void MainWindow::saveFile()
{
        for(auto& openFile: openFiles)
            if(openFile.getTextEdit() == senderTextEdit)
            {
                if(openFile.getName().isEmpty() || openFile.getName() == "no name")
                    saveFileAs();

                if(!openFile.getPath().isEmpty()){

                    if (openFile.getPath().length() > 0){
                        QString ext = QString(&(openFile.getPath().data()[openFile.getPath().length() - 4]));
                        if (ext == ".txt"){
                            QFile file(openFile.getPath());
                            if (file.open(QFile::WriteOnly /* | QFile::NewOnly */)){
                                QTextStream stream(&file);
                                stream << senderTextEdit->toPlainText();
                                file.close();
                            }
                        }
                    }

                }
            }

}

void MainWindow::saveFileAs()
{
    QString fileName =
            QFileDialog::getSaveFileName
            (this, tr("Сохранить как..."), fileSystemViwer->getCurrentPath(), filterForNameFile);

        if(!fileName.isEmpty())
            if (fileName.length() > 0){
                QString ext = QString(&(fileName.data()[fileName.length() - 4]));
                if (ext == ".txt"){
                    QFile file(fileName);
                    if (file.open(QFile::WriteOnly /* | QFile::NewOnly */)){
                        QTextStream stream(&file);
                        stream << senderTextEdit->toPlainText();
                        file.close();

                        for(auto& openFile: openFiles)
                            if(openFile.getTextEdit() == senderTextEdit){
                                openFile.changePath(fileName);
                                openFile.rename(getCorrectName(fileName));
                                ui->tabWidget->setTabText(ui->tabWidget->currentIndex(),openFile.getName());
                            }
                    }
                }
            }

}

void MainWindow::openFileReadWrite()
{
    QString fileName = QFileDialog::getOpenFileName
            (this, tr("открыть для редактирования"),fileSystemViwer->getCurrentPath(), filterForNameFile);

    openFile(fileName,false);
}

void MainWindow::openFileReadOnly()
{
    QString fileName = QFileDialog::getOpenFileName
            (this, tr("открыть без редактирования"), fileSystemViwer->getCurrentPath(), filterForNameFile);

    openFile(fileName,true);
}

void MainWindow::openFile(QString fileName,bool isReadOnly)
{
    if (fileName.length() > 0){
        int index = fileName.indexOf(".txt");
        if (index != -1 && fileName.length() - 4 == index){
            QFile file(fileName);
            if (file.open(QFile::ReadOnly | QFile::ExistingOnly)){
               QTextStream stream(&file);
               QTextEdit* textEdit = new QTextEdit;
               textEdit->setPlainText(stream.readAll());
               textEdit->setReadOnly(isReadOnly);
               OpenFile openFile(getCorrectName(fileName),fileName,textEdit);
               senderTextEdit = textEdit;
               openFiles.append(openFile);
               ui->tabWidget->insertTab(0,textEdit,openFile.getName());
               ui->tabWidget->setCurrentIndex(0);
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
        return "no name";

    QString ext = QString(&(fileName.data()[fileName.length() - 4]));
    if (ext != ".txt")
        fileName += ".txt";

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

void MainWindow::addTab(int index)
{
    QTextEdit* textEdit = new QTextEdit;
    senderTextEdit = textEdit;

    if(ui->tabWidget->tabText(index) == "+"){
        OpenFile openFile(getCorrectName(""),fileSystemViwer->getCurrentPath(),textEdit);
        openFiles.append(openFile);
        ui->tabWidget->insertTab(index,textEdit,openFile.getName());
        ui->tabWidget->setCurrentIndex(index);
        ui->menuSave->setEnabled(true);
        ui->menuCloseFile->setEnabled(true);
    }
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
    disconnect(ui->tabWidget, SIGNAL(tabBarClicked(int)),this, SLOT(addTab(int)));
    disconnect(ui->tabWidget, SIGNAL(currentChanged(int)),this, SLOT(addTab(int)));

    delete fileSystemViwer;
    delete ui;
}
