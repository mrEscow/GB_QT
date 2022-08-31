#ifndef MULTILINGUALTEXTEDIT_H
#define MULTILINGUALTEXTEDIT_H

#include <QTextEdit>

class MultilingualTextEdit : public QTextEdit
{
    Q_OBJECT
public:
    explicit MultilingualTextEdit(QTextEdit *parent = nullptr);
protected:
    void contextMenuEvent(QContextMenuEvent *event) override;
public slots:
    void undoText();
    void redoText();
    void cutText();
    void copyText();
    void pasteText();
    void deleteText();
    void selectAllText();
private:
    QMenu *menu;
};

#endif // MULTILINGUALTEXTEDIT_H
