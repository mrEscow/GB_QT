#include "ParametersWidget.h"
#include "qdebug.h"
#include "qdiriterator.h"
#include "ui_ParametersWidget.h"
#include <QTranslator>
#include <QEvent>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QFileDialog>

ParametersWidget::ParametersWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ParametersWidget)
{
    ui->setupUi(this);
    this->setWindowIcon(QIcon(":/Images/Icons/settings.png"));
    this->setWindowTitle(tr("Параменты"));
    installEventFilter(this);
    settings = new QSettings(this);

    loadSettings();

    connect(ui->pushButtonOpen, SIGNAL(clicked()), this, SLOT(onOpenButton()));
}

ParametersWidget::~ParametersWidget()
{
    saveSettings();
    delete ui;
}

void ParametersWidget::setLocalLanguage()
{
    QString localPostfics = QLocale::system().name();
    for(auto& postfics: languagesPostfics)
        if(localPostfics.contains(postfics))
            switchLanguage(languagesPostfics.indexOf(postfics));
}

void ParametersWidget::setLanguage()
{
    switchLanguage(ui->comboBoxLanguages->currentIndex());
}

void ParametersWidget::setStyleSheet()
{
    setStyleSheet(ui->comboBoxStyles->currentIndex());
}

void ParametersWidget::switchLanguage(int activItemID)
{
    QTranslator translator;
    QString path = ":/Languages/QtLanguage_" + languagesPostfics.at(activItemID);
    translator.load(path);

    qApp->installTranslator(&translator);

    this->setWindowTitle(tr("Параменты"));
    ui->language->setText(tr("Язык:"));
    ui->labelStyle->setText(tr("Стиль:"));

    ui->labeKeybord->setText(tr("Клавиатура:"));
    ui->labelAction->setText(tr("Действие"));
    ui->labelModifilter->setText(tr("Модификатор"));
    ui->labelKey->setText(tr("Клавиша"));

    ui->labelOpen->setText(tr("Открыть"));
    ui->labelSaveAs->setText(tr("Сохранить как"));
    ui->labelCreateFile->setText(tr("Создать файл"));
    ui->labelExit->setText(tr("Выход"));

    ui->labelHomeDirectory->setText(tr("Домашний каталог:"));
    ui->pushButtonOpen->setText(tr("Открыть"));

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

void ParametersWidget::loadSettings()
{
    loadLanguage();
    loadStyle();
    loadShortcuts();
    loadHomeDirectory();
}

void ParametersWidget::loadLanguage()
{
    settings->beginGroup("Language");
        auto index = settings->value("Language",0).toInt();
    settings->endGroup();

    ui->comboBoxLanguages->addItem(QIcon("://Images/Flags/russia.jpg"),"Русский");
    languagesPostfics.push_back("ru");
    ui->comboBoxLanguages->addItem(QIcon("://Images/Flags/english.jpg"),"English");
    languagesPostfics.push_back("en");
    ui->comboBoxLanguages->addItem(QIcon("://Images/Flags/japan.jpg"),"日本語");
    languagesPostfics.push_back("ja");

    ui->comboBoxLanguages->setCurrentIndex(index);
    connect(ui->comboBoxLanguages,SIGNAL(activated(int)),SLOT(switchLanguage(int)));
    switchLanguage(index);
}

void ParametersWidget::loadStyle()
{
    settings->beginGroup("Style");
        auto index = settings->value("Style",0).toInt();
    settings->endGroup();

    QDirIterator ItR("://Styles/", QDir::Files);
    while(ItR.hasNext()) {
        QFile file(ItR.next());
        if(file.open(QFile::ReadOnly)) {

            QString styleSheet = file.readAll();
            styles.push_back(styleSheet);

            QString name = file.fileName().mid(10, file.fileName().count() - 10 - 4);
            ui->comboBoxStyles->addItem(name);

            file.close();
        }

    }

    ui->comboBoxStyles->setCurrentIndex(index);
    connect(ui->comboBoxStyles,SIGNAL(activated(int)),SLOT(setStyleSheet(int)));
}

void ParametersWidget::loadShortcuts()
{
    settings->beginGroup("Shortcuts");

        QPair<Qt::KeyboardModifier,Qt::Key> open;
        open.first = settings->value("OpenModifier", Qt::ControlModifier).value<Qt::KeyboardModifier>();
        open.second = settings->value("OpenKey", Qt::Key_O).value<Qt::Key>();

        QPair<Qt::KeyboardModifier,Qt::Key> saveAs;
        saveAs.first = settings->value("SaveAsModifier", Qt::ControlModifier).value<Qt::KeyboardModifier>();
        saveAs.second = settings->value("SaveAsKey", Qt::Key_S).value<Qt::Key>();

        QPair<Qt::KeyboardModifier,Qt::Key> createFile;
        createFile.first = settings->value("CreateFileModifier", Qt::ControlModifier).value<Qt::KeyboardModifier>();
        createFile.second = settings->value("CreateFileKey", Qt::Key_N).value<Qt::Key>();

        QPair<Qt::KeyboardModifier,Qt::Key> exit;
        exit.first = settings->value("ExitModifier", Qt::ControlModifier).value<Qt::KeyboardModifier>();
        exit.second = settings->value("ExitKey", Qt::Key_Q).value<Qt::Key>();

    settings->endGroup();

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

void ParametersWidget::loadHomeDirectory()
{
    settings->beginGroup("Directory");
        homeDirectory = settings->value("HomeDirectory",QDir::current().path()).toString();
    settings->endGroup();

    ui->lineEditPath->setText(homeDirectory);
    emit changeHomeDirectory(homeDirectory);
}

void ParametersWidget::saveSettings()
{
    saveLanguage();
    saveStyle();
    saveShortcuts();
    saveHomeDirectory();
}

void ParametersWidget::saveLanguage()
{
    settings->beginGroup("Language");
        settings->setValue("Language",ui->comboBoxLanguages->currentIndex());
    settings->endGroup();
}

void ParametersWidget::saveStyle()
{
    settings->beginGroup("Style");
        settings->setValue("Style",ui->comboBoxStyles->currentIndex());
    settings->endGroup();
}

void ParametersWidget::saveShortcuts()
{
    settings->beginGroup("Shortcuts");
        settings->setValue("OpenModifier",shortcutsList[0].getModifier());
        settings->setValue("OpenKey",shortcutsList[0].getKey());
        settings->setValue("SaveAsModifier",shortcutsList[1].getModifier());
        settings->setValue("SaveAsKey",shortcutsList[1].getKey());
        settings->setValue("CreateFileModifier",shortcutsList[2].getModifier());
        settings->setValue("CreateFileKey",shortcutsList[2].getKey());
        settings->setValue("ExitModifier",shortcutsList[3].getModifier());
        settings->setValue("ExitKey",shortcutsList[3].getKey());
    settings->endGroup();
}

void ParametersWidget::saveHomeDirectory()
{
    settings->beginGroup("Directory");
        settings->setValue("HomeDirectory", homeDirectory);
    settings->endGroup();
}

QList<Shortcut> ParametersWidget::getShortcuts()
{
    return shortcutsList;
}

void ParametersWidget::setStyleSheet(int index)
{
    qApp->setStyleSheet(styles[index]);
}

const QString &ParametersWidget::getHomeDirectory()
{
    return homeDirectory;
}

void ParametersWidget::onOpenButton()
{
    homeDirectory = QFileDialog::getExistingDirectory(this, tr("Открыть каталог"),
                                                 "",
                                                 QFileDialog::ShowDirsOnly
                                                 | QFileDialog::DontResolveSymlinks);
    ui->lineEditPath->setText(homeDirectory);
    emit changeHomeDirectory(homeDirectory);
}
