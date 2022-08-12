#include "ParametersWidget.h"
#include "qdebug.h"
#include "ui_ParametersWidget.h"
#include <QTranslator>

ParametersWidget::ParametersWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ParametersWidget)
{
    ui->setupUi(this);
    this->setWindowTitle(tr("Параменты"));

    ui->comboBox->addItem(tr("Русский"));
    languagesPostfics.push_back("ru");
    ui->comboBox->addItem(tr("Английский"));
    languagesPostfics.push_back("en");
    ui->comboBox->addItem(tr("Японский"));
    languagesPostfics.push_back("ja");

    connect(ui->comboBox,SIGNAL(activated(int)),SLOT(switchLanguage(int)));

}

ParametersWidget::~ParametersWidget()
{
    delete ui;
}

void ParametersWidget::switchLanguage(int activItemID)
{
    QTranslator translator;
    QString path = "languages/QtLanguage_" + languagesPostfics.at(activItemID);
    translator.load(path);

    bool isGood = qApp->installTranslator(&translator);
    qDebug() << path << isGood;

    this->setWindowTitle(tr("Параменты"));
    ui->language->setText(tr("Язык:"));
    ui->comboBox->setItemText(0,tr("Русский"));
    ui->comboBox->setItemText(1,tr("Английский"));
    ui->comboBox->setItemText(2,tr("Японский"));

    emit switchLanguage();
}
