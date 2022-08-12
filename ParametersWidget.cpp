#include "ParametersWidget.h"
#include "qdebug.h"
#include "ui_ParametersWidget.h"
#include <QTranslator>
#include <QEvent>
#include <QMouseEvent>
#include <QKeyEvent>

ParametersWidget::ParametersWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ParametersWidget)
{
    ui->setupUi(this);
    this->setWindowTitle(tr("Параменты"));

    ui->comboBoxLanguages->addItem(tr("Русский"));
    languagesPostfics.push_back("ru");
    ui->comboBoxLanguages->addItem(tr("Английский"));
    languagesPostfics.push_back("en");
    ui->comboBoxLanguages->addItem(tr("Японский"));
    languagesPostfics.push_back("ja");

    connect(ui->comboBoxLanguages,SIGNAL(activated(int)),SLOT(switchLanguage(int)));

    modifiers.append("NO MOD");
    modifiers.append("Shift ");
    modifiers.append("Ctrl  ");
    modifiers.append("Alt   ");

    ui->comboBoxOpen->addItems(modifiers);
    ui->comboBoxSave_as->addItems(modifiers);
    ui->comboBoxCreateFile->addItems(modifiers);
    ui->comboBoxExit->addItems(modifiers);

//    connect(ui->comboBox,SIGNAL(activated(int)),SLOT(switchLanguage(int)));
//    connect(ui->comboBox,SIGNAL(activated(int)),SLOT(switchLanguage(int)));
//    connect(ui->comboBox,SIGNAL(activated(int)),SLOT(switchLanguage(int)));
//    connect(ui->comboBox,SIGNAL(activated(int)),SLOT(switchLanguage(int)));

    lineEdits.push_back(ui->lineEditOpen);
    lineEdits.push_back(ui->lineEditSave_as);
    lineEdits.push_back(ui->lineEditCreateFile);
    lineEdits.push_back(ui->lineEditExit);

    shortcuts.open.first = Qt::ControlModifier;
    shortcuts.open.second = Qt::Key_O;
    shortcuts.save_as.first = Qt::ControlModifier;
    shortcuts.save_as.second = Qt::Key_S;
    shortcuts.createFile.first = Qt::ControlModifier;
    shortcuts.createFile.second = Qt::Key_N;
    shortcuts.exit.first = Qt::ControlModifier;
    shortcuts.exit.second = Qt::Key_Q;

    setKeyParamInWidget();

    installEventFilter(this);

    for(auto& lineEdit:lineEdits){
        lineEdit->installEventFilter(this);
        lineEdit->setEnabled(false);
        lineEdit->setReadOnly(true);
    }
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
    ui->comboBoxLanguages->setItemText(0,tr("Русский"));
    ui->comboBoxLanguages->setItemText(1,tr("Английский"));
    ui->comboBoxLanguages->setItemText(2,tr("Японский"));

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

void ParametersWidget::setNewKeyFromLineEdit()
{
    qDebug() << "setNewKeyFromLineEdit";
    QObject* obj = sender();

    QLineEdit* someLineEdit = qobject_cast<QLineEdit*>(obj);
    if(!someLineEdit)
        return;
    QString oldKey;
    oldKey = someLineEdit->text();
    someLineEdit->clear();
    qDebug() << "someLineEdit->clear()";
    someLineEdit->setText(oldKey);
}

bool ParametersWidget::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == ui->lineEditOpen && event->type() == QEvent::MouseButtonPress){
       QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);
       if(mouseEvent != 0 && mouseEvent->button() == Qt::LeftButton)
            celectLineEditFromFilter(ui->lineEditOpen);
    }

    if(watched == ui->lineEditSave_as && event->type() == QEvent::MouseButtonPress){
       QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);
       if(mouseEvent != 0 && mouseEvent->button() == Qt::LeftButton)
            celectLineEditFromFilter(ui->lineEditSave_as);
    }

    if(watched == ui->lineEditCreateFile && event->type() == QEvent::MouseButtonPress){
       QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);
       if(mouseEvent != 0 && mouseEvent->button() == Qt::LeftButton)
            celectLineEditFromFilter(ui->lineEditCreateFile);
    }

    if(watched == ui->lineEditExit && event->type() == QEvent::MouseButtonPress){
       QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);
       if(mouseEvent != 0 && mouseEvent->button() == Qt::LeftButton)
           celectLineEditFromFilter(ui->lineEditExit);
    }

    if(watched == this && event->type() == QEvent::MouseButtonPress){
        closeLineEditors();
    }

    if(isChangeKey){
        if(watched  == this && event->type() == QEvent::KeyPress){
            QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);

            newKey = QKeySequence(keyEvent->key()).toString();

            if(isModifaerKey(keyEvent->key()))
                if(!isSuchPair(keyEvent->key())){
                    oldKey = newKey;
                    closeLineEditors();
                    setKeyParamInStruct();
                }
        }
    }

    return qApp->eventFilter(watched, event);
}

void ParametersWidget::celectLineEditFromFilter(QLineEdit* lE)
{
    if(!lE->isEnabled()){
        for(auto& lineEdit: lineEdits)
            if(lineEdit->isEnabled()){
                lineEdit->setText(oldKey);
                lineEdit->setEnabled(false);
         }
        isChangeKey = true;
        oldKey = lE->text();
        lE->clear();
        lE->setEnabled(true);
        testLineEdit = lE;
    }
}

bool ParametersWidget::isModifaerKey(int key)
{
    if(key == Qt::Key_Shift) return false;
    if(key == Qt::Key_Control) return false;
    if(key == Qt::Key_Meta) return false;
    if(key == Qt::Key_Alt) return false;
    if(key == Qt::Key_CapsLock) return false;
    if(key == Qt::Key_NumLock) return false;
    if(key == Qt::Key_ScrollLock) return false;
    return true;
}

bool ParametersWidget::isSuchPair(const int& key)
{
    if(testLineEdit){
        if(testLineEdit == ui->lineEditOpen){
            if(shortcuts.save_as.second == key) return true;
            if(shortcuts.createFile.second == key) return true;
            if(shortcuts.exit.second == key) return true;
        }
        if(testLineEdit == ui->lineEditSave_as){
            if(shortcuts.open.second == key) return true;
            if(shortcuts.createFile.second == key) return true;
            if(shortcuts.exit.second == key) return true;
        }
        if(testLineEdit == ui->lineEditCreateFile){
            if(shortcuts.open.second == key) return true;
            if(shortcuts.save_as.second == key) return true;
            if(shortcuts.exit.second == key) return true;
        }
        if(testLineEdit == ui->lineEditExit){
            if(shortcuts.open.second == key) return true;
            if(shortcuts.save_as.second == key) return true;
            if(shortcuts.createFile.second == key) return true;
        }
    }
    return false;
}

void ParametersWidget::closeLineEditors()
{
    isChangeKey = false;

    for(auto& lineEdit: lineEdits){
        if(lineEdit->isEnabled()){
            lineEdit->setText(oldKey);
            lineEdit->setEnabled(false);
        }
    }
}

void ParametersWidget::setKeyParamInStruct()
{
    shortcuts.open.second = (Qt::Key)QKeySequence(ui->lineEditOpen->text())[0];
    shortcuts.save_as.second = (Qt::Key)QKeySequence(ui->lineEditSave_as->text())[0];
    shortcuts.createFile.second = (Qt::Key)QKeySequence(ui->lineEditCreateFile->text())[0];
    shortcuts.exit.second = (Qt::Key)QKeySequence(ui->lineEditExit->text())[0];
}

