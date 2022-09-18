#include "FileSystemViewer.h"
#include "Escow.h"
//#include "qstandarditemmodel.h"


FileSystemViewer::FileSystemViewer(QPushButton *home,
        QPushButton *up,
        QPushButton *search,
        QLineEdit *lineEditDir,
        QLineEdit *lineEditFile,
        QListView *listView
        ) : QObject(nullptr)
{
    homeButton.reset(home);
    upButton.reset(up);
    searchButton.reset(search);
    this->lineEditDir.reset(lineEditDir);
    this->lineEditFile.reset(lineEditFile);
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

    controller = new Controller(this);
    connect(controller, SIGNAL(changFindPath(QString)), SLOT(changStatusLabel(QString)));
    connect(controller, SIGNAL(genPathOfFile(QString)), SLOT(printFindFile(QString)));
    //connect(controller, SIGNAL((newFind())), infoText, SLOT(clear()));
}

FileSystemViewer::~FileSystemViewer()
{
    delete model;
}

void FileSystemViewer::setRootPathAndIndex(const QString &path){
    currentPath = path;
    model->setRootPath(currentPath);
    listView->setRootIndex(model->index(currentPath));
    lineEditDir->setText(currentPath);
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
    if(dir.cdUp())
        setRootPathAndIndex(dir.absolutePath());
    else
        setRootPathAndIndex("");
}

void FileSystemViewer::onSearchButton()
{
    fileList.clear();

    QString testPath = lineEditDir->text();

    if(QDir(testPath).exists()){
        setRootPathAndIndex(testPath);
        findFileSlot();
    }
    else
        lineEditDir->setText(currentPath);
}

void FileSystemViewer::onDoublCliced(QModelIndex index)
{
    if(isItemModel){
        QString filePath = index.data().toString();
        emit openFile(filePath,false);
        return;
    }

    QFileInfo fileInfo = model->fileInfo(index);

    if(fileInfo.isDir())
        setRootPathAndIndex(fileInfo.absoluteFilePath());

    if(fileInfo.isFile())
        emit openFile(fileInfo.absoluteFilePath(),false);
}

void FileSystemViewer::findFileSlot()
{
    QString fileName = lineEditFile->text();
    if (fileName.length() == 0){
        fileList.clear();
        listView->setModel(model);
        setRootPathAndIndex(homePath);
        isItemModel = false;
        return;
    }
    controller->startFind(lineEditDir->text() + "/", fileName);
}
void FileSystemViewer::changStatusLabel(QString line)
{
    emit newStatusLabel(line);
}
void FileSystemViewer::printFindFile(QString str)
{
    fileList << str;

    QStandardItemModel *itemModel = new QStandardItemModel  (this);
    for(const auto& namefile :fileList)
        itemModel->appendRow(new QStandardItem(namefile));

    listView->setModel(itemModel);
    isItemModel = true;
}
