#include "RecordForm.h"
#include "ui_RecordForm.h"

RecordForm::RecordForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RecordForm)
{
    ui->setupUi(this);

    mapper = new QDataWidgetMapper(this);
    mapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);

    connect(ui->pushButton_Apple,SIGNAL(clicked()),this,SLOT(onSubmit()));
    connect(ui->pushButton_Close,SIGNAL(clicked()),this,SLOT(onClose()));
}

RecordForm::~RecordForm()
{
    delete ui;
}

void RecordForm::setModel(QAbstractItemModel *model)
{
    mapper->setModel(model);

    mapper->addMapping(ui->lineEdit_Name,0);
    mapper->addMapping(ui->label_IP,1);
    mapper->addMapping(ui->label_MAC,2);
}

QDataWidgetMapper *RecordForm::getMapper()
{
    return mapper;
}

void RecordForm::onSubmit()
{
    qDebug() << "mapperSubmit";

    mapper->submit();
}

void RecordForm::onClose()
{
    qDebug() << "closeRecordForm";
    close();
}
