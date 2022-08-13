#include "Shortcut.h"
#include <QDebug>

Shortcut::Shortcut(QLabel* name,
                   QComboBox* comboBox,
                   QLineEdit* lineEdit,
                   QPair<Qt::KeyboardModifier,Qt::Key> shortcut)

{
    this->name.reset( name );
    this->comboBox.reset(comboBox);
    this->lineEdit.reset(lineEdit);
    this->shortcut = shortcut;

    modifiers.append("NO MOD");
    modifiers.append("Shift ");
    modifiers.append("Ctrl  ");
    modifiers.append("Alt   ");

    this->comboBox.data()->addItems(modifiers);

    setKeyParamInWidgets();
}

QLabel *Shortcut::getName()
{
    return name.data();
}

QComboBox *Shortcut::getComboBox()
{
    return comboBox.data();
}

QLineEdit *Shortcut::getLineEdit()
{
    return lineEdit.data();
}

QPair<Qt::KeyboardModifier, Qt::Key> Shortcut::getShortcut()
{
    return shortcut;
}

Qt::KeyboardModifier Shortcut::getModifier()
{
    return shortcut.first;
}

Qt::Key Shortcut::getKey()
{
    return shortcut.second;
}

void Shortcut::setShortcut(QPair<Qt::KeyboardModifier, Qt::Key> shortcut)
{
    this->shortcut = shortcut;
}

void Shortcut::setKeyboardModifier(Qt::KeyboardModifier modifier)
{
    shortcut.first = modifier;
}

void Shortcut::setKey(Qt::Key key)
{
    shortcut.second = key;
};

void Shortcut::setKeyParamInWidgets()
{
    setModifierForCombobox(shortcut.first, comboBox.data());
    setKeyForLineEdit(shortcut.second, lineEdit.data());
}

void Shortcut::setModifierForCombobox(const Qt::KeyboardModifier& modifilter,QComboBox* box)
{
    if(modifilter == Qt::NoModifier)
        box->setCurrentIndex(0);
    if(modifilter == Qt::ShiftModifier)
        box->setCurrentIndex(1);
    if(modifilter == Qt::ControlModifier)
        box->setCurrentIndex(2);
    if(modifilter == Qt::AltModifier)
        box->setCurrentIndex(3);
}

void Shortcut::setKeyForLineEdit(const Qt::Key &key, QLineEdit *lineEdit)
{
    lineEdit->setText(QKeySequence(key).toString());
}
