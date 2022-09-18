QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Controller.cpp \
    FileCreatorWidget.cpp \
    FileSystemViewer.cpp \
    HTMLHighLighter.cpp \
    HelpWidget.cpp \
    MultilingualTextEdit.cpp \
    OpenFile.cpp \
    ParametersWidget.cpp \
    Shortcut.cpp \
    ThreadFinder.cpp \
    main.cpp \
    MainWindow.cpp

HEADERS += \
    Controller.h \
    Escow.h \
    FileCreatorWidget.h \
    FileSystemViewer.h \
    HTMLHighLighter.h \
    HelpWidget.h \
    MainWindow.h \
    MultilingualTextEdit.h \
    OpenFile.h \
    ParametersWidget.h \
    Shortcut.h \
    ThreadFinder.h

FORMS += \
    FileCreatorWidget.ui \
    HelpWidget.ui \
    MainWindow.ui \
    ParametersWidget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Resources.qrc

TRANSLATIONS += Languages/QtLanguage_en.ts \
                Languages/QtLanguage_ru.ts \
                Languages/QtLanguage_ja.ts

CODECFORSRC = UTF-8
