#include "MainWindow.h"
#include "ui_MainWindow.h"

#include "Wgt_RootQuadraticEquationSecondDegree.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    auto FirstTask = new Wgt_RootQuadraticEquationSecondDegree(this);


}

MainWindow::~MainWindow()
{
    delete ui;
}

