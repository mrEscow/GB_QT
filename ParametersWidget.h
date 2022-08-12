#ifndef PARAMETERSWIDGET_H
#define PARAMETERSWIDGET_H

#include <QWidget>
#include <QStringList>

namespace Ui {
class ParametersWidget;
}

class ParametersWidget : public QWidget
{
    Q_OBJECT

    struct Shortcuts{
        QPair<Qt::Modifier,Qt::Key> open;
        QPair<Qt::Modifier,Qt::Key> save_as;
        QPair<Qt::Modifier,Qt::Key> createFile;
        QPair<Qt::Modifier,Qt::Key> exit;
    };

public:
    explicit ParametersWidget(QWidget *parent = nullptr);
    ~ParametersWidget();
private slots:
    void switchLanguage(int);
signals:
    void switchLanguage();
private:
    Ui::ParametersWidget *ui;
    QStringList languagesPostfics;
};

#endif // PARAMETERSWIDGET_H
