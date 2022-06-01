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
    itemModel->appendRow(
                new QStandardItem(QIcon(QApplication::style()->standardIcon(QStyle::SP_FileIcon)),
                "Строка с файлом"));
    itemModel->appendRow(
                new QStandardItem(QIcon(QApplication::style()->standardIcon(QStyle::SP_MediaPlay)),
                "Медиа"));
    itemModel->appendRow(
                new QStandardItem(QIcon("./demo.png"),
                "Из файла"));



    strModel  = new QStringListModel    (this);
    QStringList list;
    list << "Строка 1" << "Строка 2" << "Строка 3" << "Строка 4";
    strModel->setStringList(list);

    //ui->listView->setViewMode();

    ui->checkBox->setText("QStringListModel");
    ui->listView->setModel(strModel);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_checkBox_clicked(bool checked)
{
    if(!checked){
        ui->listView->setModel(strModel);
        ui->checkBox->setText("QStringListModel");
    }
    else{
        ui->listView->setModel(itemModel);
        ui->checkBox->setText("QStandardItemModel");
    }

}

