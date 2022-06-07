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
    //QTableView::seleselectionModel();
    //QItemSelectionModel *c = ui->tableView->selectionModel();
    //ui->tableView->setSpan(c.);

    //ui->tableView->setSpan(0, 2, 3,1); // объединение строк в 3 столбце

    auto selection_model = ui->tableView->selectionModel();
    if(selection_model->hasSelection()){
        auto selected_indexes =selection_model->selectedIndexes();
        int r{0};
        int c{0};
        int rs{0};
        int cs{0};
        qDebug() << "Size"<< selected_indexes.size();
        if(selected_indexes.size()>1){
            for(auto index : selected_indexes){

                if(r >= index.row())
                    r = index.row();
                if(c >= index.column())
                    c =index.column();

                if(rs <= index.row())
                    rs = index.row();
                if(cs <= index.column())
                    cs =index.column();
                qDebug() << r << c;
                qDebug() << rs << cs;
            }

            ui->tableView->setSpan(r, c, rs + 1, cs + 1);
        }
    }
}

void MainWindow::onColor()
{


    //auto x = ui->tableView->itemDelegate();

    //auto x = ui->tableView->currentIndex();
    //auto y = ui->tableView->selectionBehavior();

    //auto z = ui->tableView->SelectedClicked;


//    int row = ui->tableView->currentIndex().row();
//    int column = ui->tableView->currentIndex().column();

//    qDebug() << row << column;// << x << y;

//    //ui->tableView->setSpan(row, column, 0,0);
//    qDebug() << ui->tableView->rowSpan(row, column);


//    QPalette p;
//    QColor color(123,45,234);
//    ColorRole x;
//    p.setColor(x,color);
//    ui->tableView->setPalette(p);


    //QItemSelectionModel *c = ui->tableView->selectionModel();
    //c->selectedIndexes()
//    ui->tableView->setSpan(
//                ui->tableView->currentIndex().column(),
//                ui->tableView->currentIndex().row(),
//                ui->tableView->currentIndex().column(),
//                ui->tableView->currentIndex().row());

    //QModelIndexList indexes =
    //model.sel
            //ui->tableView->selectAll();//->selectedRows();
    //auto selectedList = ui->tableView->selectionBehavior();
    //qDebug() << selectedList;
}
