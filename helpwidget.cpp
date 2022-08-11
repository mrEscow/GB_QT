#include "HelpWidget.h"
#include "ui_HelpWidget.h"

HelpWidget::HelpWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HelpWidget)
{
    ui->setupUi(this);
}

HelpWidget::~HelpWidget()
{
    delete ui;
}

void HelpWidget::setText(QString text)
{
    ui->textBrowser->setText(text);
}

void HelpWidget::setLabelText(QString text)
{
    ui->label->setText(text);
}
