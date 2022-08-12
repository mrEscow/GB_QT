#ifndef PARAMETERSWIDGET_H
#define PARAMETERSWIDGET_H

#include "qcombobox.h"
#include <QWidget>
#include <QStringList>

namespace Ui {
class ParametersWidget;
}

class ParametersWidget : public QWidget
{
    Q_OBJECT

    struct Shortcuts{
        QPair<Qt::KeyboardModifier,Qt::Key> open;
        QPair<Qt::KeyboardModifier,Qt::Key> save_as;
        QPair<Qt::KeyboardModifier,Qt::Key> createFile;
        QPair<Qt::KeyboardModifier,Qt::Key> exit;
    };

public:
    explicit ParametersWidget(QWidget *parent = nullptr);
    ~ParametersWidget();
private slots:
    void switchLanguage(int);
signals:
    void switchLanguage();
private:
    void setKeyParamInWidget();
    void setModifierForCombobox(const Qt::KeyboardModifier& modifilter, QComboBox* box);
    void setKeyForLineEdit(const Qt::Key& key, QLineEdit* lineEdit);
private:
    Ui::ParametersWidget *ui;
    QStringList languagesPostfics;
    Shortcuts shortcuts;
    QStringList modifiers;
};

#endif // PARAMETERSWIDGET_H
