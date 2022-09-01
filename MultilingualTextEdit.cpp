#include "MultilingualTextEdit.h"

#include "Escow.h"

#include <QMenu>
#include <QContextMenuEvent>

QString MultilingualTextEdit::undo = tr("&Назад\tCtrl+Z");
QString MultilingualTextEdit::redo = tr("&Вперед\tCtrl+Y");;
QString MultilingualTextEdit::cut = tr("&Вырезать\tCtrl+X");
QString MultilingualTextEdit::copy = tr("&Копировать\tCtrl+C");
QString MultilingualTextEdit::paste = tr("&Вставить\tCtrl+V");
QString MultilingualTextEdit::del = tr("&Удалить");
QString MultilingualTextEdit::selectAll = tr("&Выбрать всё\tCtrl+A");

MultilingualTextEdit::MultilingualTextEdit(QWidget *parent)
    :QTextEdit(parent)
{
}

void MultilingualTextEdit::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu *menu = QTextEdit::createStandardContextMenu();

    QList<QAction*> actions = menu->actions();
    actions[0]->setText(undo);
    actions[1]->setText(redo);
    actions[3]->setText(cut);
    actions[4]->setText(copy);
    actions[5]->setText(paste);
    actions[6]->setText(del);
    actions[8]->setText(selectAll);

    menu->exec(event->globalPos());
}

void MultilingualTextEdit::switchLanguage()
{
    undo = tr("&Назад\tCtrl+Z");
    redo = tr("&Вперед\tCtrl+Y");
    cut = tr("&Вырезать\tCtrl+X");
    copy = tr("&Копировать\tCtrl+C");
    paste = tr("&Вставить\tCtrl+V");
    del = tr("&Удалить");
    selectAll = tr("&Выбрать всё\tCtrl+A");
}

