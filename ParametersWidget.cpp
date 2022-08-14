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

    ui->labeKeybord->setText(tr("Клавиатура:"));
    ui->labelAction->setText(tr("Действие"));
    ui->labelModifilter->setText(tr("Модификатор"));
    ui->labelKey->setText(tr("Клавиша"));

    ui->labelOpen->setText(tr("Открыть"));
    ui->labelSaveAs->setText(tr("Сохранить как"));
    ui->labelCreateFile->setText(tr("Создать файл"));
    ui->labelExit->setText(tr("Выход"));

    connect(ui->comboBoxLanguages,SIGNAL(activated(int)),SLOT(switchLanguage(int)));

    QPair<Qt::KeyboardModifier,Qt::Key> open;
    open.first = Qt::ControlModifier;
    open.second = Qt::Key_O;

    QPair<Qt::KeyboardModifier,Qt::Key> saveAs;
    saveAs.first = Qt::ControlModifier;
    saveAs.second = Qt::Key_S;

    QPair<Qt::KeyboardModifier,Qt::Key> createFile;
    createFile.first = Qt::ControlModifier;
    createFile.second = Qt::Key_N;

    QPair<Qt::KeyboardModifier,Qt::Key> exit;
    exit.first = Qt::ControlModifier;
    exit.second = Qt::Key_Q;

    shortcutsList.push_back(Shortcut(ui->labelOpen,ui->comboBoxOpen,ui->lineEditOpen,open));
    shortcutsList.push_back(Shortcut(ui->labelSaveAs,ui->comboBoxSaveAs,ui->lineEditSaveAs,saveAs));
    shortcutsList.push_back(Shortcut(ui->labelCreateFile,ui->comboBoxCreateFile,ui->lineEditCreateFile,createFile));
    shortcutsList.push_back(Shortcut(ui->labelExit,ui->comboBoxExit,ui->lineEditExit,exit));

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

void ParametersWidget::setLocalLanguage()
{
    QString localPostfics = QLocale::system().name();
    for(auto& postfics: languagesPostfics)
        if(localPostfics.contains(postfics))
            switchLanguage(languagesPostfics.indexOf(postfics));

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

    ui->labeKeybord->setText(tr("Клавиатура:"));
    ui->labelAction->setText(tr("Действие"));
    ui->labelModifilter->setText(tr("Модификатор"));
    ui->labelKey->setText(tr("Клавиша"));

    ui->labelOpen->setText(tr("Открыть"));
    ui->labelSaveAs->setText(tr("Сохранить как"));
    ui->labelCreateFile->setText(tr("Создать файл"));
    ui->labelExit->setText(tr("Выход"));

    emit changeLanguage();
}

void ParametersWidget::setNewModifierFromCombobox(int index)
{
    QObject* obj = sender();

    senderComboBox = qobject_cast<QComboBox*>(obj);
    if(!senderComboBox)
        return;

    Qt::KeyboardModifier newModifier = getKeyboardModifier(index);
    if(!isSuchPair(newModifier))
        setKeyParamInShortcutsAndApp();
    else        
        senderComboBox->setCurrentIndex(oldCurrentIndex);
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

bool ParametersWidget::eventFilter(QObject *watched, QEvent *event)
{
    for(auto& shortcut: shortcutsList){
        if(watched == shortcut.getComboBox() && event->type() == QEvent::MouseButtonPress)
            oldCurrentIndex = shortcut.getComboBox()->currentIndex();
        if(watched == shortcut.getLineEdit() && event->type() == QEvent::MouseButtonPress){
           QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);
           if(mouseEvent != 0 && mouseEvent->button() == Qt::LeftButton)
               celectLineEditFromFilter(shortcut.getLineEdit());
        }
    }

    if(watched == this && event->type() == QEvent::MouseButtonPress){
        isChangeKey = false;
        closeLineEditors();
    }

    if(isChangeKey)
        if(watched  == this && event->type() == QEvent::KeyPress){
            QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);
            testAndSetNewKey(keyEvent);
        }

    return qApp->eventFilter(watched, event);
}

void ParametersWidget::celectLineEditFromFilter(QLineEdit* lineEdit)
{
    if(!lineEdit->isEnabled()){
        closeLineEditors();
        currentKey = lineEdit->text();
        lineEdit->clear();
        lineEdit->setEnabled(true);
        isChangeKey = true;
        senderLineEdit = lineEdit;
    }
}

void ParametersWidget::testAndSetNewKey(QKeyEvent *keyEvent)
{
    if(!isModifaerKey((Qt::Key)keyEvent->key()) && !isSuchPair((Qt::Key)keyEvent->key())){
            currentKey = QKeySequence(keyEvent->key()).toString();
            isChangeKey = false;
            closeLineEditors();
            setKeyParamInShortcutsAndApp();
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
        if(senderLineEdit == shortcut.getLineEdit()){
            QPair<Qt::KeyboardModifier,Qt::Key> testPair(shortcut.getModifier(),key);
            for(auto& shortcutPair: shortcutsList)
                if(shortcutPair.getShortcut() == testPair)
                    return true;
        }

    return false;
}

void ParametersWidget::closeLineEditors()
{
    for(auto& shortcut: shortcutsList)
        if(shortcut.getLineEdit()->isEnabled()){
            shortcut.getLineEdit()->setText(currentKey);
            shortcut.getLineEdit()->setEnabled(false);
        }
}

void ParametersWidget::setKeyParamInShortcutsAndApp()
{
    for(auto& shortcut : shortcutsList){
        shortcut.setKeyboardModifier(getKeyboardModifier(shortcut.getComboBox()->currentIndex()));
        shortcut.setKey((Qt::Key)QKeySequence(shortcut.getLineEdit()->text())[0]);
    }

    emit changeShortcuts(shortcutsList);
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

QList<Shortcut> ParametersWidget::getShortcuts()
{
    return shortcutsList;
}
