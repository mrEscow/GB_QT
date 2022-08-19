#include "FileSystemViewer.h"
#include "qdebug.h"

FileSystemViewer::FileSystemViewer(
        QPushButton *home,
        QPushButton *up,
        QPushButton *search,
        QLineEdit *lineEdit,
        QListView *listView
        ) : QObject(nullptr)
{
    homeButton.reset(home);
    upButton.reset(up);
    searchButton.reset(search);
    this->lineEdit.reset(lineEdit);
    this->listView.reset(listView);

    model = new QFileSystemModel(this);
    model->setFilter(QDir::Files | QDir::AllDirs | QDir::NoDotAndDotDot);
    model->setNameFilters (QStringList () << "*.txt");
    model->setRootPath(QDir::current().path());


    listView->setContextMenuPolicy(Qt::CustomContextMenu);
    listView->setModel(model);

    connect(homeButton.data(), SIGNAL(clicked()), this, SLOT(onHomeButton()));
    connect(upButton.data(), SIGNAL(clicked()), this, SLOT(onUpButton()));
    connect(searchButton.data(), SIGNAL(clicked()), this, SLOT(onSearchButton()));

    connect(listView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(onDoublCliced(QModelIndex)));
}

FileSystemViewer::~FileSystemViewer()
{
    delete model;
}

void FileSystemViewer::setRootPathAndIndex(const QString &path){
    currentPath = path;
    model->setRootPath(currentPath);
    listView->setRootIndex(model->index(currentPath));
    lineEdit->setText(currentPath);
}

void FileSystemViewer::setHomePath(const QString &path)
{
    homePath = path;
}

const QString &FileSystemViewer::getCurrentPath()
{
    return currentPath;
}

void FileSystemViewer::onHomeButton()
{
    setRootPathAndIndex(homePath);
}

void FileSystemViewer::onUpButton()
{
    QDir dir = model->rootDirectory();
    if(dir.cdUp()){
        setRootPathAndIndex(dir.absolutePath());
        emit newPath(dir.absolutePath());
    }
    else{
        setRootPathAndIndex("");
        emit newPath("");
    }
}

void FileSystemViewer::onSearchButton()
{
    QString testPath = lineEdit->text();

    if(QDir(testPath).exists()){
        setRootPathAndIndex(testPath);
    }
    else
        lineEdit->setText(currentPath);
}

void FileSystemViewer::onDoublCliced(QModelIndex index)
{
    QFileInfo fileInfo = model->fileInfo(index);

    if(fileInfo.isDir()){
        setRootPathAndIndex(fileInfo.absoluteFilePath());
        emit newPath(fileInfo.absoluteFilePath());
    }

    if(fileInfo.isFile())
        emit openFile(fileInfo.absoluteFilePath());
}
