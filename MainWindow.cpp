#include "MainWindow.h"
#include "ui_MainWindow.h"

#include "Wgt_RootQuadraticEquationSecondDegree.h"
#include "Wgt_CalculationSideTriangle_onTwoSides_and_AngleBetween.h"

#include <QLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    auto MAIN_WGT = new QWidget(this);
    MAIN_WGT->resize(this->size());

    auto FirstTask = new Wgt_RootQuadraticEquationSecondDegree(MAIN_WGT);
    auto SecondTask = new Wgt_CalculationSideTriangle_onTwoSides_and_AngleBetween(MAIN_WGT);
    //auto TheeTask = new Wgt_Two_TextEditors_with_html(this);

    auto Vertical_Layout = new QVBoxLayout(MAIN_WGT);
    Vertical_Layout->addWidget(FirstTask);
    Vertical_Layout->addWidget(SecondTask);
    //Vertical_Layout->addWidget(TheeTask);

}

MainWindow::~MainWindow()
{
    delete ui;
}

