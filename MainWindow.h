#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include "HelpWidget.h"
#include "FileCreatorWidget.h"
#include "ParametersWidget.h"
#include <qfilesystemmodel.h>

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
    QFileSystemModel *fileSystemModel;

};
#endif // MAINWINDOW_H
