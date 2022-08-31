#include "MultilingualTextEdit.h"

#include <QMenu>
#include <QContextMenuEvent>
//#include <QApplication>
//#include <QClipboard>

#include <QDebug>
#define q (qDebug() << "MY_DEBUG: ")

MultilingualTextEdit::MultilingualTextEdit(QWidget *parent)
    :QTextEdit(parent)
{

}

void MultilingualTextEdit::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu *menu = QTextEdit::createStandardContextMenu();

    QList<QAction*> actions = menu->actions();

    actions[0]->setText(tr("&Назад\tCtrl+Z"));
    actions[1]->setText(tr("&Вперед\tCtrl+Y"));
    actions[3]->setText(tr("&Вырезать\tCtrl+X"));
    actions[4]->setText(tr("&Копировать\tCtrl+C"));
    actions[5]->setText(tr("&Вставить\tCtrl+V"));
    actions[6]->setText(tr("&Удалить"));
    actions[8]->setText(tr("&Выбрать всё\tCtrl+A"));

    menu->exec(event->globalPos());
}

//void MultilingualTextEdit::undoText()
//{
//    QTextEdit::undo();
//}

//void MultilingualTextEdit::redoText()
//{
//    QTextEdit::redo();
//}

//void MultilingualTextEdit::cutText()
//{
//    QTextEdit::cut();
//}

//void MultilingualTextEdit::copyText()
//{
//    QTextEdit::copy();
////    QString str = this->textCursor().selectedText();
////    qApp->clipboard()->setText(str);
//}

//void MultilingualTextEdit::pasteText()
//{
//    QTextEdit::paste();
////    QString str = qApp->clipboard()->text();
////    this->textCursor().insertText(str);
//}

//void MultilingualTextEdit::deleteText()
//{
//    //QTextEdit::clear();
//    //QTextEdit::
//    //QTextEdit::_q_deleteSelected();
//}

//void MultilingualTextEdit::selectAllText()
//{
//    QTextEdit::selectAll();
//}
