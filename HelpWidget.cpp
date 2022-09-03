#include "HelpWidget.h"
#include "qdebug.h"
#include "qicon.h"
#include "ui_HelpWidget.h"
#include <QFile>

HelpWidget::HelpWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HelpWidget)
{
    ui->setupUi(this);
    ui->textBrowser->setReadOnly(true);
    ui->textBrowser->setAlignment(Qt::AlignCenter);
    this->setWindowIcon(QIcon(":/Images/Icons/about.png"));
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
        tr("Добро пожаловать в текстовый редактор!"),
        tr("Здесь вы можете загружать файлы с расширением txt,"),
        tr("редактировать их и сохранять."),
        tr("Спасибо что прочитали!"),
        tr("удачи!")
    };
    ui->textBrowser->clear();

    QFont font = ui->textBrowser->textCursor().charFormat().font();
    font.setBold(true);
    ui->textBrowser->setFont(font);
    ui->textBrowser->setAlignment(Qt::AlignCenter);

    for(auto &text: list)
        ui->textBrowser->append(text);
}
