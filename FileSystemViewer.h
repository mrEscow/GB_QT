#ifndef FILESYSTEMVIEWER_H
#define FILESYSTEMVIEWER_H

#include "Controller.h"
#include "qstandarditemmodel.h"
#include <QObject>
#include <QSharedPointer>
#include <QFileSystemModel>
#include <QPushButton>
#include <QLineEdit>
#include <QListView>

class FileSystemViewer : public QObject
{
    Q_OBJECT
public:
    FileSystemViewer(
            QPushButton* home,
            QPushButton* up,
            QPushButton* search,
            QLineEdit* lineEditDir,
            QLineEdit* lineEditFile,
            QListView* listView
            );
    ~FileSystemViewer();
public slots:
    void setRootPathAndIndex(const QString& path);
    void setHomePath(const QString& path);
    const QString& getCurrentPath();
private slots:
    void onHomeButton();
    void onUpButton();
    void onSearchButton();
    void onDoublCliced(QModelIndex index);

signals:
    void openFile(QString newPath,bool isReadOnly);
private slots:
    void findFileSlot();
    void changStatusLabel(QString);
    void printFindFile(QString);
signals:
    void newStatusLabel(QString);
private:
    QFileSystemModel *model;
    QString homePath;
    QString currentPath;
    QSharedPointer<QPushButton> homeButton;
    QSharedPointer<QPushButton> upButton;
    QSharedPointer<QPushButton> searchButton;
    QSharedPointer<QLineEdit> lineEditDir;
    QSharedPointer<QLineEdit> lineEditFile;
    QSharedPointer<QListView> listView;

    Controller *controller;
    QStringList fileList;
    bool isItemModel;
    QStandardItemModel *itemModel;
};

#endif // FILESYSTEMVIEWER_H
