#ifndef HELPWIDGET_H
#define HELPWIDGET_H

#include <QWidget>

namespace Ui {
class HelpWidget;
}

class HelpWidget : public QWidget
{
    Q_OBJECT

public:
    explicit HelpWidget(QWidget *parent = nullptr);
    ~HelpWidget();
public:
    void setText(QString text);
    void setLabelText(QString text);
private:
    Ui::HelpWidget *ui;
};

#endif // HELPWIDGET_H
