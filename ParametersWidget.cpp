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
    installEventFilter(this);

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

    comboBoxes.push_back(ui->comboBoxOpen);
    comboBoxes.push_back(ui->comboBoxSaveAs);
    comboBoxes.push_back(ui->comboBoxCreateFile);
    comboBoxes.push_back(ui->comboBoxExit);

    for(auto& comboBox: comboBoxes){
        comboBox->addItems(modifiers);
        comboBox->setTabletTracking(false);
        comboBox->installEventFilter(this);
        connect(comboBox,SIGNAL(activated(int)),SLOT(setNewModifierFromCombobox(int)));
    }


    lineEdits.push_back(ui->lineEditOpen);
    lineEdits.push_back(ui->lineEditSaveAs);
    lineEdits.push_back(ui->lineEditCreateFile);
    lineEdits.push_back(ui->lineEditExit);

    for(auto& lineEdit:lineEdits){
        lineEdit->installEventFilter(this);
        lineEdit->setEnabled(false);
        lineEdit->setReadOnly(true);
    }

    shortcuts.open.first = Qt::ControlModifier;
    shortcuts.open.second = Qt::Key_O;
    shortcuts.saveAs.first = Qt::ControlModifier;
    shortcuts.saveAs.second = Qt::Key_S;
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
    ui->comboBoxLanguages->setItemText(0,tr("Русский"));
    ui->comboBoxLanguages->setItemText(1,tr("Английский"));
    ui->comboBoxLanguages->setItemText(2,tr("Японский"));

    emit changeLanguage();
}

void ParametersWidget::setKeyParamInWidget()
{
    setModifierForCombobox(shortcuts.open.first, ui->comboBoxOpen);
    setModifierForCombobox(shortcuts.saveAs.first, ui->comboBoxSaveAs);
    setModifierForCombobox(shortcuts.createFile.first, ui->comboBoxCreateFile);
    setModifierForCombobox(shortcuts.exit.first, ui->comboBoxExit);

    setKeyForLineEdit(shortcuts.open.second, ui->lineEditOpen);
    setKeyForLineEdit(shortcuts.saveAs.second, ui->lineEditSaveAs);
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

void ParametersWidget::setNewModifierFromCombobox(int index)
{
    QObject* obj = sender();

    testComboBox = qobject_cast<QComboBox*>(obj);
    if(!testComboBox)
        return;

    //testComboBox->currentIndexChanged();

    Qt::KeyboardModifier tempTestModifier;

    switch(index){
        case 0:
            tempTestModifier = Qt::NoModifier;
        break;
        case 1:
            tempTestModifier = Qt::ShiftModifier;
        break;
        case 2:
            tempTestModifier = Qt::ControlModifier;
        break;
        case 3:
            tempTestModifier = Qt::AltModifier;
        break;
    }

    if(isSuchPair(tempTestModifier))
        testComboBox->setCurrentIndex(oldCurrentIndex);
    else
        setKeyParamInStruct();
}



bool ParametersWidget::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == ui->comboBoxOpen && event->type() == QEvent::MouseButtonPress)
        oldCurrentIndex = ui->comboBoxOpen->currentIndex();

    if(watched == ui->comboBoxSaveAs && event->type() == QEvent::MouseButtonPress)
        oldCurrentIndex = ui->comboBoxSaveAs->currentIndex();

    if(watched == ui->comboBoxCreateFile && event->type() == QEvent::MouseButtonPress)
        oldCurrentIndex = ui->comboBoxCreateFile->currentIndex();

    if(watched == ui->comboBoxExit && event->type() == QEvent::MouseButtonPress)
        oldCurrentIndex = ui->comboBoxExit->currentIndex();


    if(watched == ui->lineEditOpen && event->type() == QEvent::MouseButtonPress){
       QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);
       if(mouseEvent != 0 && mouseEvent->button() == Qt::LeftButton)
            celectLineEditFromFilter(ui->lineEditOpen);
    }

    if(watched == ui->lineEditSaveAs && event->type() == QEvent::MouseButtonPress){
       QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);
       if(mouseEvent != 0 && mouseEvent->button() == Qt::LeftButton)
            celectLineEditFromFilter(ui->lineEditSaveAs);
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

    if(watched == this && event->type() == QEvent::MouseButtonPress)
        closeLineEditors();


    if(isChangeKey){
        if(watched  == this && event->type() == QEvent::KeyPress){
            QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);

            newKey = QKeySequence(keyEvent->key()).toString();

            if(!isModifaerKey(keyEvent->key())){
                if(!isSuchPair(keyEvent->key())){
                    oldKey = newKey;
                    closeLineEditors();
                    setKeyParamInStruct();
                }
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

bool ParametersWidget::isModifaerKey(const int& key)
{
    if(key == Qt::Key_Shift) return true;
    if(key == Qt::Key_Control) return true;
    if(key == Qt::Key_Meta) return true;
    if(key == Qt::Key_Alt) return true;
    if(key == Qt::Key_CapsLock) return true;
    if(key == Qt::Key_NumLock) return true;
    if(key == Qt::Key_ScrollLock) return true;
    return false;
}

bool ParametersWidget::isSuchPair(const int& key)
{

    if(testLineEdit == ui->lineEditOpen){
        QPair<Qt::KeyboardModifier,Qt::Key> temp(shortcuts.open.first,(Qt::Key)key);
        if(shortcuts.saveAs == temp) return true;
        if(shortcuts.createFile == temp) return true;
        if(shortcuts.exit == temp) return true;
    }
    if(testLineEdit == ui->lineEditSaveAs){
        QPair<Qt::KeyboardModifier,Qt::Key> temp(shortcuts.saveAs.first,(Qt::Key)key);
        if(shortcuts.open == temp) return true;
        if(shortcuts.createFile == temp) return true;
        if(shortcuts.exit == temp) return true;
    }
    if(testLineEdit == ui->lineEditCreateFile){
        QPair<Qt::KeyboardModifier,Qt::Key> temp(shortcuts.createFile.first,(Qt::Key)key);
        if(shortcuts.open == temp) return true;
        if(shortcuts.saveAs == temp) return true;
        if(shortcuts.exit == temp) return true;
    }
    if(testLineEdit == ui->lineEditExit){
        QPair<Qt::KeyboardModifier,Qt::Key> temp(shortcuts.exit.first,(Qt::Key)key);
        if(shortcuts.open == temp) return true;
        if(shortcuts.saveAs == temp) return true;
        if(shortcuts.createFile == temp) return true;
    }

    return false;
}

bool ParametersWidget::isSuchPair(const Qt::KeyboardModifier &modifier)
{
    if(testComboBox == ui->comboBoxOpen){
        QPair<Qt::KeyboardModifier,Qt::Key> temp(modifier,(Qt::Key)QKeySequence(ui->lineEditOpen->text())[0]);
        if(shortcuts.saveAs == temp) return true;
        if(shortcuts.createFile == temp) return true;
        if(shortcuts.exit == temp) return true;
    }
    if(testComboBox == ui->comboBoxSaveAs){
        QPair<Qt::KeyboardModifier,Qt::Key> temp(modifier,(Qt::Key)QKeySequence(ui->lineEditSaveAs->text())[0]);
        if(shortcuts.open == temp) return true;
        if(shortcuts.createFile == temp) return true;
        if(shortcuts.exit == temp) return true;
    }
    if(testComboBox == ui->comboBoxCreateFile){
        QPair<Qt::KeyboardModifier,Qt::Key> temp(modifier,(Qt::Key)QKeySequence(ui->lineEditCreateFile->text())[0]);
        if(shortcuts.open == temp) return true;
        if(shortcuts.saveAs == temp) return true;
        if(shortcuts.exit == temp) return true;
    }
    if(testComboBox == ui->comboBoxExit){
        QPair<Qt::KeyboardModifier,Qt::Key> temp(modifier,(Qt::Key)QKeySequence(ui->lineEditExit->text())[0]);
        if(shortcuts.open == temp) return true;
        if(shortcuts.saveAs == temp) return true;
        if(shortcuts.createFile == temp) return true;
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
    shortcuts.saveAs.second = (Qt::Key)QKeySequence(ui->lineEditSaveAs->text())[0];
    shortcuts.createFile.second = (Qt::Key)QKeySequence(ui->lineEditCreateFile->text())[0];
    shortcuts.exit.second = (Qt::Key)QKeySequence(ui->lineEditExit->text())[0];

    shortcuts.open.first = getKeyboardModifier(ui->comboBoxOpen);
    shortcuts.saveAs.first = getKeyboardModifier(ui->comboBoxSaveAs);
    shortcuts.createFile.first = getKeyboardModifier(ui->comboBoxCreateFile);
    shortcuts.exit.first = getKeyboardModifier(ui->comboBoxExit);

    emit changeShortcuts();
}

Qt::KeyboardModifier ParametersWidget::getKeyboardModifier(QComboBox* comboBox)
{
    Qt::KeyboardModifier keyboardModifier;

    switch(comboBox->currentIndex()){
        case 0:
            keyboardModifier = Qt::NoModifier;
        break;
        case 1:
            keyboardModifier = Qt::ShiftModifier;
        break;
        case 2:
            keyboardModifier = Qt::ControlModifier;
        break;
        case 3:
            keyboardModifier = Qt::AltModifier;
        break;
    }

    return keyboardModifier;
}

Shortcuts ParametersWidget::getShortcuts()
{
    return shortcuts;
}

