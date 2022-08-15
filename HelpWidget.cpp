#include "HelpWidget.h"
#include "qdebug.h"
#include "ui_HelpWidget.h"
#include <QFile>

HelpWidget::HelpWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HelpWidget)
{
    ui->setupUi(this);
    ui->textBrowser->setReadOnly(true);
    this->setWindowTitle(tr("Справка"));
    ui->label->setText(tr("О программе !"));
    QFile file(":/HelpText.txt");
    QString helpText;
    if (file.open(QIODevice::ReadOnly)){
        QTextStream stream(&file);
        helpText = stream.readAll();
        file.close();
    }
    ui->textBrowser->setText(helpText);
}

HelpWidget::~HelpWidget()
{
    delete ui;
}

void HelpWidget::switchLanguage()
{
    this->setWindowTitle(tr("Справка"));
    ui->label->setText(tr("О программе !"));

    QString list[] =
    {
        tr("\tДобро пожаловать в текстовый редактор!"),
        tr("\tЗдесь вы можете загружать файлы с расширением txt,"),
        tr("\tредактировать их и сохранять."),
        tr("\tСпасибо что прочитали!"),
        tr("\tудачи!")
    };
    ui->textBrowser->clear();
    for(auto &text: list)
        ui->textBrowser->append(text);
}
