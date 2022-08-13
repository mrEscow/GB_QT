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

    shortcuts.open.first = Qt::ControlModifier;
    shortcuts.open.second = Qt::Key_O;
    shortcuts.saveAs.first = Qt::ControlModifier;
    shortcuts.saveAs.second = Qt::Key_S;
    shortcuts.createFile.first = Qt::ControlModifier;
    shortcuts.createFile.second = Qt::Key_N;
    shortcuts.exit.first = Qt::ControlModifier;
    shortcuts.exit.second = Qt::Key_Q;

    shortcutsList.push_back(Shortcut(ui->labelOpen,ui->comboBoxOpen,ui->lineEditOpen,shortcuts.open));
    shortcutsList.push_back(Shortcut(ui->labelSaveAs,ui->comboBoxSaveAs,ui->lineEditSaveAs,shortcuts.saveAs));
    shortcutsList.push_back(Shortcut(ui->labelCreateFile,ui->comboBoxCreateFile,ui->lineEditCreateFile,shortcuts.createFile));
    shortcutsList.push_back(Shortcut(ui->labelExit,ui->comboBoxExit,ui->lineEditExit,shortcuts.exit));

    for(auto& shortcut: shortcutsList){
        shortcut.getComboBox()->setTabletTracking(false);
        shortcut.getComboBox()->installEventFilter(this);
        connect(shortcut.getComboBox(),SIGNAL(activated(int)),SLOT(setNewModifierFromCombobox(int)));
        shortcut.getLineEdit()->installEventFilter(this);
        shortcut.getLineEdit()->setEnabled(false);
        shortcut.getLineEdit()->setReadOnly(true);
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

    emit changeLanguage();
}

void ParametersWidget::setNewModifierFromCombobox(int index)
{
    QObject* obj = sender();

    senderComboBox = qobject_cast<QComboBox*>(obj);
    if(!senderComboBox)
        return;

    Qt::KeyboardModifier newModifier = getKeyboardModifier(index);

    if(isSuchPair(newModifier))
        senderComboBox->setCurrentIndex(oldCurrentIndex);
    else
        setKeyParamInStruct();
}

bool ParametersWidget::eventFilter(QObject *watched, QEvent *event)
{
    for(auto& shortcut: shortcutsList)
        if(watched == shortcut.getComboBox() && event->type() == QEvent::MouseButtonPress)
            oldCurrentIndex = shortcut.getComboBox()->currentIndex();

    for(auto& shortcut: shortcutsList)
        if(watched == shortcut.getLineEdit() && event->type() == QEvent::MouseButtonPress){
           QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);
           if(mouseEvent != 0 && mouseEvent->button() == Qt::LeftButton)
               celectLineEditFromFilter(shortcut.getLineEdit());
        }


    if(watched == this && event->type() == QEvent::MouseButtonPress)
        closeLineEditors();

    if(isChangeKey){
        if(watched  == this && event->type() == QEvent::KeyPress){
            QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);
            if(!isModifaerKey((Qt::Key)keyEvent->key()) && !isSuchPair((Qt::Key)keyEvent->key())){
                    oldKey = QKeySequence(keyEvent->key()).toString();
                    closeLineEditors();
                    setKeyParamInStruct();
            }
        }
    }

    return qApp->eventFilter(watched, event);
}

void ParametersWidget::celectLineEditFromFilter(QLineEdit* lineEdit)
{
    if(!lineEdit->isEnabled()){

        for(auto& shortcut: shortcutsList)
            if(shortcut.getLineEdit()->isEnabled()){
                shortcut.getLineEdit()->setText(oldKey);
                shortcut.getLineEdit()->setEnabled(false);
            }

        isChangeKey = true;
        oldKey = lineEdit->text();
        lineEdit->clear();
        lineEdit->setEnabled(true);
        senderLineEdit = lineEdit;
    }
}

bool ParametersWidget::isModifaerKey(const Qt::Key& key)
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

bool ParametersWidget::isSuchPair(const Qt::Key& key)
{
    for(auto& shortcut: shortcutsList)
        if(shortcut.getLineEdit() == senderLineEdit){
            QPair<Qt::KeyboardModifier,Qt::Key> testPair(shortcut.getModifier(),key);
            for(auto& shortcutPair: shortcutsList)
                if(shortcutPair.getShortcut() == testPair)
                    return true;
        }

    return false;
}

bool ParametersWidget::isSuchPair(const Qt::KeyboardModifier &modifier)
{
    for(auto& shortcut: shortcutsList)
        if(senderComboBox == shortcut.getComboBox()){
            QPair<Qt::KeyboardModifier,Qt::Key> testPair(modifier, shortcut.getKey());
            for(auto& shortcutPair: shortcutsList)
                if(shortcutPair.getShortcut() == testPair)
                    return true;
        }

    return false;
}

void ParametersWidget::closeLineEditors()
{
    isChangeKey = false;

    for(auto& shortcut: shortcutsList){
        if(shortcut.getLineEdit()->isEnabled()){
            shortcut.getLineEdit()->setText(oldKey);
            shortcut.getLineEdit()->setEnabled(false);
        }
    }
}

void ParametersWidget::setKeyParamInStruct()
{
    for(auto& shortcuts : shortcutsList){
        shortcuts.setKeyboardModifier(getKeyboardModifier(shortcuts.getComboBox()->currentIndex()));
        shortcuts.setKey((Qt::Key)QKeySequence(shortcuts.getLineEdit()->text())[0]);
    }

    shortcuts.open.second = (Qt::Key)QKeySequence(ui->lineEditOpen->text())[0];
    shortcuts.saveAs.second = (Qt::Key)QKeySequence(ui->lineEditSaveAs->text())[0];
    shortcuts.createFile.second = (Qt::Key)QKeySequence(ui->lineEditCreateFile->text())[0];
    shortcuts.exit.second = (Qt::Key)QKeySequence(ui->lineEditExit->text())[0];

    shortcuts.open.first = getKeyboardModifier(ui->comboBoxOpen->currentIndex());
    shortcuts.saveAs.first = getKeyboardModifier(ui->comboBoxSaveAs->currentIndex());
    shortcuts.createFile.first = getKeyboardModifier(ui->comboBoxCreateFile->currentIndex());
    shortcuts.exit.first = getKeyboardModifier(ui->comboBoxExit->currentIndex());

    emit changeShortcuts();
}

Qt::KeyboardModifier ParametersWidget::getKeyboardModifier(const int& currentIndex)
{
    Qt::KeyboardModifier keyboardModifier;

    switch(currentIndex){
        case 0: keyboardModifier = Qt::NoModifier; break;
        case 1: keyboardModifier = Qt::ShiftModifier;break;
        case 2: keyboardModifier = Qt::ControlModifier;break;
        case 3: keyboardModifier = Qt::AltModifier;break;
        default:keyboardModifier = Qt::NoModifier;break;
    }

    return keyboardModifier;
}

Shortcuts ParametersWidget::getShortcuts()
{
    return shortcuts;
}

