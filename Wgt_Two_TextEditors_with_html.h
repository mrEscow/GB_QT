#ifndef WGT_TWO_TEXTEDITORS_WITH_HTML_H
#define WGT_TWO_TEXTEDITORS_WITH_HTML_H

#include <QWidget>
#include <QPlainTextEdit>

class Wgt_Two_TextEditors_with_html : public QWidget
{
    Q_OBJECT
public:
    Wgt_Two_TextEditors_with_html(QWidget * parent = nullptr);
private slots:
    void AddText();
private:
    QPlainTextEdit *PlainTextOne;
    QPlainTextEdit *PlainTextTwo;
};

#endif // WGT_TWO_TEXTEDITORS_WITH_HTML_H
