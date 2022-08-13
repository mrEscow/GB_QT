#ifndef SHORTCUT_H
#define SHORTCUT_H


#include "qcombobox.h"
#include "qlabel.h"
#include "qlineedit.h"
#include "qnamespace.h"

class Shortcut{
    QSharedPointer<QLabel> name;
    QSharedPointer<QComboBox> comboBox;
    QSharedPointer<QLineEdit> lineEdit;
    QPair<Qt::KeyboardModifier,Qt::Key> shortcut;
    QStringList modifiers;
public:
    Shortcut(QLabel* name,
             QComboBox* comboBox,
             QLineEdit* lineEdit,
             QPair<Qt::KeyboardModifier,Qt::Key> shortcut);


    QLabel* getName();
    QComboBox* getComboBox();
    QLineEdit *getLineEdit();

    QPair<Qt::KeyboardModifier,Qt::Key> getShortcut();
    Qt::KeyboardModifier getModifier();

    Qt::Key getKey();

    void setShortcut(QPair<Qt::KeyboardModifier,Qt::Key> shortcut);
    void setKeyboardModifier(Qt::KeyboardModifier modifier);
    void setKey(Qt::Key key);
private:
    void setKeyParamInWidgets();
    void setModifierForCombobox(const Qt::KeyboardModifier& modifilter, QComboBox* box);
    void setKeyForLineEdit(const Qt::Key& key, QLineEdit* lineEdit);

};

#endif // SHORTCUT_H
