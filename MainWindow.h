#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include "HelpWidget.h"
#include "FileCreatorWidget.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void createFile();
    void getNamefile(QString);
    void saveFile();
    void saveFile_as();
    void openFile();
    void openFile_as();
    void exit();
    void parametrs();
    void help();

private:
    Ui::MainWindow *ui;
    QString filter;
    HelpWidget helpWidget;
    FileCreatorWidget fileCreatorWidget;
    QString fileName;
};
#endif // MAINWINDOW_H
