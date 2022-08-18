#include "FileSystemViewer.h"
#include "qdebug.h"


FileSystemViewer::FileSystemViewer(QObject* parrent) : QObject(parrent)
{
    widget = new QWidget();
    upButton = new QPushButton("Up",widget);
    model = new QFileSystemModel(widget);
    listView = new QListView(widget);
    layout = new QVBoxLayout(widget);

    model->setFilter(QDir::Files | QDir::AllDirs | QDir::NoDotAndDotDot);
    model->setNameFilters (QStringList () << "*.txt");
    model->setRootPath(QDir::current().path());

    listView->setContextMenuPolicy(Qt::CustomContextMenu);
    listView->setModel(model);

    layout->addWidget(upButton);
    layout->addWidget(listView);

    widget->setLayout(layout);

    connect(upButton, SIGNAL(clicked()), this, SLOT(onUpButton()));
    connect(listView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(onDoublCliced(QModelIndex)));
}

FileSystemViewer::~FileSystemViewer()
{
    delete widget;
}

QWidget *FileSystemViewer::operator()()
{
    return widget;
}

void FileSystemViewer::setRootPathAndIndex(const QString &path){
    model->setRootPath(path);
    listView->setRootIndex(model->index(path));
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
