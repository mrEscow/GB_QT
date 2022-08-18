#ifndef FILESYSTEMVIEWER_H
#define FILESYSTEMVIEWER_H

#include <QWidget>
#include "qboxlayout.h"
#include "qfilesystemmodel.h"
#include "qlistview.h"
#include "qpushbutton.h"

class FileSystemViewer : public QObject
{
    Q_OBJECT
public:
    FileSystemViewer(QObject* parrent = nullptr);
    ~FileSystemViewer();

    QWidget* operator()();

    void setRootPathAndIndex(const QString& path);

private slots:
    void onUpButton();
    void onDoublCliced(QModelIndex index);

signals:
    void newPath(QString newPath);
    void openFile(QString newPath);
private:
    QListView* listView;
    QFileSystemModel *model;
    QPushButton* upButton;
    QVBoxLayout* layout;
    QWidget* widget;
};

#endif // FILESYSTEMVIEWER_H
