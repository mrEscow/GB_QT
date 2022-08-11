#ifndef FILECREATORWIDGET_H
#define FILECREATORWIDGET_H

#include <QWidget>

namespace Ui {
class FileCreatorWidget;
}

class FileCreatorWidget : public QWidget
{
    Q_OBJECT

public:
    explicit FileCreatorWidget(QWidget *parent = nullptr);
    ~FileCreatorWidget();
private slots:
    void create();
    void cancel();
signals:
    void newNameFromFileCreator(QString);
private slots:
    void switchLanguage();

private:
    Ui::FileCreatorWidget *ui;
    QString fileName;
};

#endif // FILECREATORWIDGET_H
