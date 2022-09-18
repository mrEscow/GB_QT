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

#include "MultilingualTextEdit.h"
#include "HTMLHighLighter.h"


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
    void setEnablets(bool);
private slots:
    void runFileCreator();
    void createFile(QString);
    void closeFile();
    void saveFile();
    void saveFileAs();
    void openFileReadWrite();
    void openFileReadOnly();
    void openFile(QString fileName,bool isReadOnly);
private:
    QString getCorrectName(QString fileName);
private slots:
    void exit();
    void parametrs();
    void help();
private slots:
    void switchLanguage();
    void changeShortcuts(QList<Shortcut> newShortcuts);
private slots:
    void addTab(int index);
    void changedTab(int index);
private slots:
    void onTabsAction();
    void onMdiAction();
    void onMdiUpdateAction();
private:
    void addSubWindow(OpenFile& file);
private slots:
    void onPrintAction();
private:
    bool eventFilter(QObject* watched, QEvent* event) override;
public:
    ~MainWindow();
private:
    void saveSettings();
private slots:
    void onSetFont();
    void onSetFontMouse();
    void onCopyFormat();
    void onSetCopyFormat();
    void onSetHTMLLighter(bool);
    void onAlignmentLeft();
    void onAlignmentRight();
    void onAlignmentCenter();
    void setAlignment(Qt::Alignment alignment);
private slots:
    void changStatusLabel(QString);
private:
    Ui::MainWindow *ui;
    QString filterForNameFile;
    HelpWidget helpWidget;
    FileCreatorWidget fileCreatorWidget;
    ParametersWidget parametersWidget;
    QList<Shortcut> shortcuts;
    MultilingualTextEdit* senderTextEdit;
    QList<OpenFile> openFiles;
    FileSystemViewer* fileSystemViwer;
    bool isMdiView;
    QSettings* settings;

    HtmlHighLighter htmlHighLighter;
    bool isHTML;
    QFont copyFont;

    QLabel *statusLabel;
};
#endif // MAINWINDOW_H
