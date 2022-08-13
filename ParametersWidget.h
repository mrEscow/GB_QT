#ifndef PARAMETERSWIDGET_H
#define PARAMETERSWIDGET_H

#include "Shortcuts.h"
#include "qcombobox.h"
#include <QWidget>
#include <QStringList>

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
private:
    void setKeyParamInWidget();
    void setModifierForCombobox(const Qt::KeyboardModifier& modifilter, QComboBox* box);
    void setKeyForLineEdit(const Qt::Key& key, QLineEdit* lineEdit);
private slots:
    void setNewModifierFromCombobox(int);
public:
    bool eventFilter(QObject *watched, QEvent *event) override;
private:
    void celectLineEditFromFilter(QLineEdit* lE);
    bool isModifaerKey(const int& key);
    bool isSuchPair(const int& key);
    bool isSuchPair(const Qt::KeyboardModifier& modifier);
    void closeLineEditors();
    void setKeyParamInStruct();
    Qt::KeyboardModifier getKeyboardModifier(QComboBox*);
signals:
    void changeShortcuts();
public:
    Shortcuts getShortcuts();
private:
    Ui::ParametersWidget *ui;
    QStringList languagesPostfics;
    Shortcuts shortcuts;
    QStringList modifiers;
    QList<QLineEdit*> lineEdits;
    QList<QComboBox*> comboBoxes;
    QLineEdit* testLineEdit;
    QComboBox* testComboBox;
    bool isChangeKey;
    QString oldKey;
    QString newKey;
    int oldCurrentIndex;


};

#endif // PARAMETERSWIDGET_H
