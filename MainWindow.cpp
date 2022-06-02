#include "MainWindow.h"
#include "ui_MainWindow.h"

/*
    Создать таблицу со столбцами: No, Имя компьютера, IP адрес, MAC адрес.
    Заполнить таблицу данными.
    Предусмотреть возможность объеденить нескольких строк в таблице (они могут идти не подряд).
    Для выделенных строк, по нажатию на кнопку покрасить задний фон в другой цвет.
*/

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    values = new QList<ComputerData>;

    values->append(ComputerData("Asus"," 192.168.1.10", "00:AB:CD:EF:11:22"));
    values->append(ComputerData("Asus"," 192.168.1.11", "00:AB:CD:EF:11:22"));
    values->append(ComputerData("Asus"," 192.168.1.12", "00:AB:CD:EF:11:22"));
    values->append(ComputerData("Asus"," 192.168.1.13", "00:AB:CD:EF:11:22"));
    values->append(ComputerData("Asus"," 192.168.1.14", "00:AB:CD:EF:11:22"));
    values->append(ComputerData("Asus"," 192.168.1.15", "00:AB:CD:EF:11:22"));


    model = new MyTableViewModel();
    model->populate(values);
    this->ui->tableView->setModel(model);




}

MainWindow::~MainWindow()
{
    delete ui;
}

