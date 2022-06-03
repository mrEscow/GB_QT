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
    ui->tableView->setModel(model);

    connect(ui->AddButton,  SIGNAL(clicked()),this, SLOT(onAdd()));
    connect(ui->DelButton,  SIGNAL(clicked()),this, SLOT(onDel()));
    connect(ui->EditButton, SIGNAL(clicked()),this, SLOT(onEdit()));
    connect(ui->AddToButton,SIGNAL(clicked()),this, SLOT(onAddTo()));

    connect(ui->SpanButton, SIGNAL(clicked()),this, SLOT(onSpan()));
    connect(ui->ColorButton,SIGNAL(clicked()),this, SLOT(onColor()));
}

MainWindow::~MainWindow()
{
    values->clear();
    delete ui;
}

void MainWindow::onAdd()
{
    model->append(ComputerData("new", "new", "new"));
}

void MainWindow::onDel()
{
    model->deleteRow(ui->tableView->currentIndex().row());
}

void MainWindow::onEdit()
{
    model->update(ui->tableView->currentIndex().row(),ComputerData("new3", "new3", "new3"));
}

void MainWindow::onAddTo()
{
    model->insertAt(ui->tableView->currentIndex().row(), ComputerData("new2", "new2", "new2"));
}

void MainWindow::onSpan()
{
    //ui->tableView->setSpan(0, 2, 3,1); // объединение строк в 3 столбце
}

void MainWindow::onColor()
{

}
