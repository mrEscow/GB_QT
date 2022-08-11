#include "FileCreatorWidget.h"
#include "qdebug.h"
#include "ui_FileCreatorWidget.h"

FileCreatorWidget::FileCreatorWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FileCreatorWidget)
{
    ui->setupUi(this);

    connect(ui->createButton,SIGNAL(clicked()),this, SLOT(create()));
    connect(ui->cancelButton,SIGNAL(clicked()),this, SLOT(cancel()));
}

FileCreatorWidget::~FileCreatorWidget()
{
    delete ui;
}

void FileCreatorWidget::create()
{
    fileName =  ui->lineEdit->text();
    if(fileName.isEmpty())
        return;
    fileName += ".txt";
    emit newNameFromFileCreator(fileName);
    fileName.clear();
    this->close();
}

void FileCreatorWidget::cancel()
{
    emit newNameFromFileCreator("");
    this->close();
}
