#include "FileCreatorWidget.h"
#include "qdebug.h"
#include "ui_FileCreatorWidget.h"

FileCreatorWidget::FileCreatorWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FileCreatorWidget)
{
    ui->setupUi(this);
    this->setWindowIcon(QIcon(":/Images/Icons/new.png"));
    this->setWindowTitle(tr("Создать файл"));

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

void FileCreatorWidget::switchLanguage()
{
    this->setWindowTitle(tr("Создать файл"));
    ui->label->setText(tr("Введите имя нового документа:"));
    ui->createButton->setText(tr("Создать"));
    ui->cancelButton->setText(tr("Отмена"));
}
