#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include "HelpWidget.h"
#include "FileCreatorWidget.h"
#include "ParametersWidget.h"
#include "Shortcuts.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

    Shortcuts shortcuts;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void runFileCreator();
    void createFile(QString);
    void closeFile();
    void saveFile();
    void saveFile_as();
    void openFileReadWrite();
    void openFileReadOnly();
private:
    void openFile(bool isReadOnly);
private slots:
    void exit();
    void parametrs();
    void help();
private slots:
    void switchLanguage();
    void changeShortcuts();
public:
    bool eventFilter(QObject* watched, QEvent* event) override;
private:
    Ui::MainWindow *ui;
    QString filter;
    HelpWidget helpWidget;
    FileCreatorWidget fileCreatorWidget;
    QString fileName;
    ParametersWidget parametersWidget;
};
#endif // MAINWINDOW_H
