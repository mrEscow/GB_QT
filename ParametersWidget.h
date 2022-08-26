#ifndef PARAMETERSWIDGET_H
#define PARAMETERSWIDGET_H

#include "Shortcut.h"
#include "qcombobox.h"
#include "qlabel.h"
#include "qlineedit.h"
#include <QWidget>
#include <QStringList>
#include <QSettings>

namespace Ui {
class ParametersWidget;
}

class ParametersWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ParametersWidget(QWidget *parent = nullptr);
    ~ParametersWidget();

public:
    void setLocalLanguage();
    void setLanguage();
    void setStyleSheet();
private slots:
    void switchLanguage(int);
signals:
    void changeLanguage();

private slots:
    void setNewModifierFromCombobox(int);
private:
    bool eventFilter(QObject *watched, QEvent *event) override;
    void celectLineEditFromFilter(QLineEdit* lE);
    bool isSuchPair(const Qt::KeyboardModifier& modifier);
    void testAndSetNewKey(QKeyEvent* keyEvent);
    bool isModifaerKey(const Qt::Key& key);
    bool isSuchPair(const Qt::Key& key);        
    void closeLineEditors();
    void setKeyParamInShortcutsAndApp();
    Qt::KeyboardModifier getKeyboardModifier(const int& currentIndex);

    void loadSettings();
    void loadLanguage();
    void loadStyle();
    void loadShortcuts();
    void loadHomeDirectory();

    void saveSettings();
    void saveLanguage();
    void saveStyle();
    void saveShortcuts();
    void saveHomeDirectory();

public:
    QList<Shortcut> getShortcuts();
signals:
    void changeShortcuts(QList<Shortcut>);

private slots:
    void setStyleSheet(int index);
public:
    const QString& getHomeDirectory();
signals:
    void changeHomeDirectory(QString directory);
private slots:
    void onOpenButton();

private:
    Ui::ParametersWidget *ui;
    QStringList languagesPostfics;
    QList<Shortcut> shortcutsList;
    QLineEdit* senderLineEdit;
    QComboBox* senderComboBox;
    bool isChangeKey;
    QString currentKey;
    int oldCurrentIndex;
    QStringList styles;
    QSettings* settings;
    QString homeDirectory;
};

Q_DECLARE_METATYPE(Qt::KeyboardModifier)

#endif // PARAMETERSWIDGET_H
