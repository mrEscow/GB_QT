#ifndef MULTILINGUALTEXTEDIT_H
#define MULTILINGUALTEXTEDIT_H

#include <QTextEdit>

class MultilingualTextEdit : public QTextEdit
{
    Q_OBJECT
public:
    explicit MultilingualTextEdit(QWidget *parent = nullptr);
protected:
    void contextMenuEvent(QContextMenuEvent *event) override;
public slots:
    void switchLanguage();
private slots:
    void onPasteTime();
private:
    static QString undo;
    static QString redo;
    static QString cut;
    static QString copy;
    static QString paste;
    static QString del;
    static QString selectAll;
    static QString pasteTime;
};

#endif // MULTILINGUALTEXTEDIT_H
