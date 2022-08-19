#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include "FileSystemViewer.h"
#include "HelpWidget.h"
#include "FileCreatorWidget.h"
#include "OpenFile.h"
#include "ParametersWidget.h"
#include "qboxlayout.h"
#include "qlistview.h"
#include "qpushbutton.h"
#include <qfilesystemmodel.h>
#include <QTextEdit>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);    
private:
    void setSettingsForThisWidgets();
    void connects();
    void setSettingsFromParametrs();
private slots:
    void runFileCreator();
    void createFile(QString);
    void closeFile();
    void saveFile();
    void saveFileAs();
    void openFileReadWrite();
    void openFileReadOnly();
    void openFile(QString fileName,bool isReadOnly);
    QString getCorrectName(QString fileName);
private slots:
    void exit();
    void parametrs();
    void help();
private slots:
    void switchLanguage();
    void changeShortcuts(QList<Shortcut> newShortcuts);
private slots:
    void addTab(int);
private:
    bool eventFilter(QObject* watched, QEvent* event) override;
public:
    ~MainWindow();
private:
    Ui::MainWindow *ui;
    QString filterForNameFile;
    HelpWidget helpWidget;
    FileCreatorWidget fileCreatorWidget;


    ParametersWidget parametersWidget;
    QList<Shortcut> shortcuts;


    QTextEdit* senderTextEdit;
    QList<OpenFile> openFiles;

    FileSystemViewer* fileSystemViwer;

};
#endif // MAINWINDOW_H
