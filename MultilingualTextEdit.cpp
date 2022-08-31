#include "MultilingualTextEdit.h"

#include <QMenu>
#include <QContextMenuEvent>
#include <QApplication>
#include <QClipboard>

MultilingualTextEdit::MultilingualTextEdit(QTextEdit *parent)
    :QTextEdit(parent)
{
    menu = new QMenu(this);
    QAction *undoAction = menu->addAction(tr("Отменить"));
    QAction *redoAction = menu->addAction(tr("Вернуть"));
    menu->addSeparator();
    QAction *cutAction = menu->addAction(tr("Вырезать"));
    QAction *copyAction = menu->addAction(tr("Копировать"));
    QAction *pastAction = menu->addAction(tr("Вставить"));
    QAction *deleteAction = menu->addAction(tr("Удалить"));
    menu->addSeparator();
    QAction *selectAllAction = menu->addAction(tr("Выбрать всё"));

    connect(undoAction, SIGNAL(triggered()), this, SLOT(undoText()));
    connect(redoAction, SIGNAL(triggered()), this, SLOT(redoText()));
    connect(cutAction, SIGNAL(triggered()), this, SLOT(cutText()));
    connect(copyAction, SIGNAL(triggered()), this, SLOT(copyText()));
    connect(pastAction, SIGNAL(triggered()), this, SLOT(pastText()));
    connect(deleteAction, SIGNAL(triggered()), this, SLOT(deleteText()));
    connect(selectAllAction, SIGNAL(triggered()), this, SLOT(selectAllText()));
}

void MultilingualTextEdit::contextMenuEvent(QContextMenuEvent *event)
{
    menu->exec(event->globalPos());
}

void MultilingualTextEdit::undoText()
{
    QTextEdit::undo();
}

void MultilingualTextEdit::redoText()
{
    QTextEdit::redo();
}

void MultilingualTextEdit::cutText()
{
    QTextEdit::cut();
}

void MultilingualTextEdit::copyText()
{
    QTextEdit::copy();
//    QString str = this->textCursor().selectedText();
//    qApp->clipboard()->setText(str);
}

void MultilingualTextEdit::pasteText()
{
    QTextEdit::paste();
//    QString str = qApp->clipboard()->text();
//    this->textCursor().insertText(str);
}

void MultilingualTextEdit::deleteText()
{
    QTextEdit::clear();
}

void MultilingualTextEdit::selectAllText()
{
    QTextEdit::selectAll();
}
