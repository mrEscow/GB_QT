#ifndef PARAMETERSWIDGET_H
#define PARAMETERSWIDGET_H

#include "Shortcut.h"
#include "qcombobox.h"
#include "qlabel.h"
#include "qlineedit.h"
#include <QWidget>
#include <QStringList>
#include <QSharedPointer>

namespace Ui {
class ParametersWidget;
}

class ParametersWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ParametersWidget(QWidget *parent = nullptr);
    ~ParametersWidget();

private slots:
    void switchLanguage(int);
signals:
    void changeLanguage();

private slots:
    void setNewModifierFromCombobox(int);
private:
    bool eventFilter(QObject *watched, QEvent *event) override;
    void celectLineEditFromFilter(QLineEdit* lE);
    bool isModifaerKey(const Qt::Key& key);
    bool isSuchPair(const Qt::Key& key);
    bool isSuchPair(const Qt::KeyboardModifier& modifier);
    void closeLineEditors();
    void setKeyParamInShortcutsAndApp();
    Qt::KeyboardModifier getKeyboardModifier(const int& currentIndex);

public:
    QList<Shortcut> getShortcuts();
signals:
    void changeShortcuts(QList<Shortcut>);

private:
    Ui::ParametersWidget *ui;
    QStringList languagesPostfics;
    QList<Shortcut> shortcutsList;
    QLineEdit* senderLineEdit;
    QComboBox* senderComboBox;
    bool isChangeKey;
    QString currentKey;
    int oldCurrentIndex;
};

#endif // PARAMETERSWIDGET_H
