#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

/*
    Создать таблицу со столбцами: No, Имя компьютера, IP адрес, MAC адрес.
    Заполнить таблицу данными.
    Предусмотреть возможность нескольких строк в таблице (они могут идти не подряд).
    Для выделенных строк, по нажатию на кнопку покрасить задний фон в другой цвет.
*/
#include "MyTableViewModel.h"
#include "computerdata.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    MyTableViewModel *model;
    QList<ComputerData> *values;
private slots:
    void onAdd();
    void onDel();
    void onEdit();
    void onAddTo();
private slots:
    void onSpan();
    void onColor();
};
#endif // MAINWINDOW_H
