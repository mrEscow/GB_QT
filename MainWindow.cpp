#include "MainWindow.h"
#include "ui_MainWindow.h"
/*
    Создать список с названиями языков программирования (С++, Python, Java, C#, PHP, JavaScript).
    Для каждого элемента списка рядом отобразить иконку с логотипом языка программирования.
    Предусмотреть возможно изменения текста в каждом элементе списка.

    Добавить возможность перемещения элементов в списке.

    Создать кнопку для добавления нового языка программирования в список.
    Иконку для него поставить любую (по-умолчанию).
    Создать кнопку для удаления элемента из списка (в этом случае элемент должен быть выбран).
    Создать CheckBox и когда будет стоять галочка, отобразить список в режиме иконок (нужен метод setViewMode()).
    Когда галочка не стоит, то список должен отображаться в обычном режиме.
    Подсказка: используйте справку qt, вызов F1.
*/
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    itemModel = new QStandardItemModel  (this);

    itemModel->appendRow(new QStandardItem(QIcon(":images/C++.png"),       "C++"));
    itemModel->appendRow(new QStandardItem(QIcon(":images/Python.png"),    "Python"));
    itemModel->appendRow(new QStandardItem(QIcon(":images/Java.png"),      "Java"));
    itemModel->appendRow(new QStandardItem(QIcon(":images/C#.png"),        "C#"));
    itemModel->appendRow(new QStandardItem(QIcon(":images/PHP.png"),       "PHP"));
    itemModel->appendRow(new QStandardItem(QIcon(":images/JavaScript.png"),"JavaScript"));

    ui->checkBox->setText("QListView::ListMode");

    ui->listView->setViewMode(QListView::ListMode);
    ui->listView->setModel(itemModel);
    ui->listView->setStyleSheet("background-color: #8B008B");

    ui->listView->setDragEnabled(true);
    ui->listView->setDropIndicatorShown(true);
    ui->listView->setDragDropMode(QAbstractItemView:: InternalMove);
    //ui->listView->setDragDropMode(QAbstractItemView:: DragDrop);

    setWindowTitle("Lesson2");
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_checkBox_clicked(bool checked)
{
    if(checked){
        ui->listView->setViewMode(QListView::IconMode);
        ui->checkBox->setText("QListView::IconMode");
    }
    else{
        ui->listView->setViewMode(QListView::ListMode);
        ui->checkBox->setText("QListView::ListMode");
    }
}


void MainWindow::on_pushButton_clicked()
{
    if(!ui->lineEdit->text().isEmpty()){
        itemModel->appendRow(new QStandardItem(QIcon(":images/New.png"),ui->lineEdit->text()));
        ui->lineEdit->clear();
    }

}


void MainWindow::on_pushButton_3_clicked()
{
    if(ui->listView->selectionModel()->hasSelection()){
        if(ui->listView->selectionModel()->currentIndex().isValid())
            itemModel->removeRow(ui->listView->selectionModel()->currentIndex().row());
    }
}

