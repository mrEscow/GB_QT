QT       += core gui qml quick quickwidgets sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    AppCore.cpp \
    ConnectionManager.cpp \
    Executor.cpp \
    Manipulator.cpp \
    Processor.cpp \
    Selector.cpp \
    Task.cpp \
    TaskManager.cpp \
    TaskModel.cpp \
    main.cpp

HEADERS += \
    AppCore.h \
    ConnectionManager.h \
    DB_Mapper.h \
    DB_Types.h \
    Executor.h \
    Manipulator.h \
    Processor.h \
    Selector.h \
    Task.h \
    TaskManager.h \
    TaskModel.h

FORMS +=

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    main.qml

RESOURCES += \
    Resources.qrc
