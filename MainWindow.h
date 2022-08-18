#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include "HelpWidget.h"
#include "FileCreatorWidget.h"
#include "ParametersWidget.h"
#include "qboxlayout.h"
#include "qlistview.h"
#include "qpushbutton.h"
#include <qfilesystemmodel.h>


class FileSystemViewer
{
public:
    FileSystemViewer()
    {
        widget = new QWidget();

        model = new QFileSystemModel();
        model->setFilter(QDir::Files | QDir::AllDirs | QDir::NoDotAndDotDot);
        model->setNameFilters (QStringList () << "*.txt");

        model->setRootPath(QDir::current().path());

        listView = new QListView();
        listView->setContextMenuPolicy(Qt::CustomContextMenu);

        listView->setModel(model);

        upButton = new QPushButton("Up");

        layout = new QVBoxLayout();
        layout->addWidget(upButton);
        layout->addWidget(listView);



        widget->setLayout(layout);
    }
    ~FileSystemViewer()
    {
        delete upButton;
        delete listView;
        delete model;
        delete layout;
        delete widget;
    }
    void setFilter(QDir::Filters filters){
        model->setFilter(filters);
    }
    void setRootPath(const QString& path){
        model->setRootPath(path);
        listView->setRootIndex(model->index(path));
    }

    QListView* getView(){
        return listView;
    }
    QFileSystemModel* getModel(){
        return model;
    }
    QWidget* getWidget(){
        return widget;
    }

private:
    QListView* listView;
    QFileSystemModel *model;
    QPushButton* upButton;
    QVBoxLayout* layout;
    QWidget* widget;
};

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);    
private:
    void connects();
    void setSettingsForThisWidgets();
    void setSettingsFromParametrs();
private slots:
    void runFileCreator();
    void createFile(QString);
    void closeFile();
    void saveFile();
    void saveFileAs();
    void openFileReadWrite();
    void openFileReadOnly();
private:
    void openFile(bool isReadOnly);
    QString getCorrectName(QString fileName);
private slots:
    void exit();
    void parametrs();
    void help();
private slots:
    void switchLanguage();
    void changeShortcuts(QList<Shortcut> newShortcuts);
private slots:
    void listViewShowContextMenu(QPoint pos);
    void listViewDoubleClicked(QModelIndex index);
private:
    bool eventFilter(QObject* watched, QEvent* event) override;
public:
    ~MainWindow();
private:
    Ui::MainWindow *ui;
    QString filterForNameFile;
    HelpWidget helpWidget;
    FileCreatorWidget fileCreatorWidget;
    QString fileName;
    ParametersWidget parametersWidget;
    QList<Shortcut> shortcuts;
    //QFileSystemModel *fileSystemModel;
    QMenu* listViewContextMenu;
    FileSystemViewer fileSystemViwer;

};
#endif // MAINWINDOW_H
