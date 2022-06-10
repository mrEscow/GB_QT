#ifndef RECORDFORM_H
#define RECORDFORM_H

#include <QWidget>
#include <QDataWidgetMapper>

namespace Ui {
class RecordForm;
}

class RecordForm : public QWidget
{
    Q_OBJECT

public:
    explicit RecordForm(QWidget *parent = nullptr);
    ~RecordForm();

    void setModel(QAbstractItemModel* model);
    QDataWidgetMapper* getMapper();
private slots:
    void onSubmit();
    void onClose();

private:
    Ui::RecordForm *ui;
    QDataWidgetMapper *mapper;
};

#endif // RECORDFORM_H
