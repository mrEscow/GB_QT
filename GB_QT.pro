QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    FileCreatorWidget.cpp \
    FileSystemViewer.cpp \
    HelpWidget.cpp \
    ParametersWidget.cpp \
    Shortcut.cpp \
    main.cpp \
    MainWindow.cpp

HEADERS += \
    FileCreatorWidget.h \
    FileSystemViewer.h \
    HelpWidget.h \
    MainWindow.h \
    ParametersWidget.h \
    Shortcut.h

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

TRANSLATIONS += QtLanguage_en.ts QtLanguage_ru.ts QtLanguage_ja.ts

CODECFORSRC = UTF-8
