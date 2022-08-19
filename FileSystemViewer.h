#ifndef FILESYSTEMVIEWER_H
#define FILESYSTEMVIEWER_H

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
            QLineEdit* lineEdit,
            QListView* listView
            );
    ~FileSystemViewer();

    void setRootPathAndIndex(const QString& path);
    void setHomePath(const QString& path);
    const QString& getCurrentPath();
private slots:
    void onHomeButton();
    void onUpButton();
    void onSearchButton();
    void onDoublCliced(QModelIndex index);

signals:
    void newPath(QString newPath);
    void openFile(QString newPath);

private:
    QFileSystemModel *model;
    QString homePath;
    QString currentPath;
    QSharedPointer<QPushButton> homeButton;
    QSharedPointer<QPushButton> upButton;
    QSharedPointer<QPushButton> searchButton;
    QSharedPointer<QLineEdit> lineEdit;
    QSharedPointer<QListView> listView;
};

#endif // FILESYSTEMVIEWER_H
