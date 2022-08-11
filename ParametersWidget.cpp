#include "ParametersWidget.h"
#include "ui_ParametersWidget.h"

ParametersWidget::ParametersWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ParametersWidget)
{
    ui->setupUi(this);

}

ParametersWidget::~ParametersWidget()
{
    delete ui;
}
