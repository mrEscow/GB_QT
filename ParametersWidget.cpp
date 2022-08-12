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

    modifiers.append("NO MOD");
    modifiers.append("Shift ");
    modifiers.append("Ctrl  ");
    modifiers.append("Alt   ");

    ui->comboBoxOpen->addItems(modifiers);
    ui->comboBoxSave_as->addItems(modifiers);
    ui->comboBoxCreateFile->addItems(modifiers);
    ui->comboBoxExit->addItems(modifiers);

    shortcuts.open.first = Qt::ControlModifier;
    shortcuts.open.second = Qt::Key_O;
    shortcuts.save_as.first = Qt::ControlModifier;
    shortcuts.save_as.second = Qt::Key_S;
    shortcuts.createFile.first = Qt::ControlModifier;
    shortcuts.createFile.second = Qt::Key_N;
    shortcuts.exit.first = Qt::ControlModifier;
    shortcuts.exit.second = Qt::Key_Q;

    setKeyParamInWidget();
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

void ParametersWidget::setKeyParamInWidget()
{
    setModifierForCombobox(shortcuts.open.first, ui->comboBoxOpen);
    setModifierForCombobox(shortcuts.save_as.first, ui->comboBoxSave_as);
    setModifierForCombobox(shortcuts.createFile.first, ui->comboBoxCreateFile);
    setModifierForCombobox(shortcuts.exit.first, ui->comboBoxExit);

    setKeyForLineEdit(shortcuts.open.second, ui->lineEditOpen);
    setKeyForLineEdit(shortcuts.save_as.second, ui->lineEditSave_as);
    setKeyForLineEdit(shortcuts.createFile.second, ui->lineEditCreateFile);
    setKeyForLineEdit(shortcuts.exit.second, ui->lineEditExit);
}

void ParametersWidget::setModifierForCombobox(const Qt::KeyboardModifier& modifilter,QComboBox* box)
{
    if(modifilter == Qt::NoModifier)
        box->setCurrentIndex(0);
    if(modifilter == Qt::ShiftModifier)
        box->setCurrentIndex(1);
    if(modifilter == Qt::ControlModifier)
        box->setCurrentIndex(2);
    if(modifilter == Qt::AltModifier)
        box->setCurrentIndex(3);
}

void ParametersWidget::setKeyForLineEdit(const Qt::Key &key, QLineEdit *lineEdit)
{
    lineEdit->setText(QKeySequence(key).toString());
}
