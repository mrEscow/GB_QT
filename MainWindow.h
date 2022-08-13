#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include "HelpWidget.h"
#include "FileCreatorWidget.h"
#include "ParametersWidget.h"

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
    void runFileCreator();
    void createFile(QString);
    void closeFile();
    void saveFile();
    void saveFileAs();
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
    void changeShortcuts(QList<Shortcut> newShortcuts);
public:
    bool eventFilter(QObject* watched, QEvent* event) override;
private:
    Ui::MainWindow *ui;
    QString filter;
    HelpWidget helpWidget;
    FileCreatorWidget fileCreatorWidget;
    QString fileName;
    ParametersWidget parametersWidget;
    QList<Shortcut> shortcuts;
};
#endif // MAINWINDOW_H
