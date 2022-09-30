#include "AppCore.h"
#include <QQmlEngine>
#include "TaskModel.h"

AppCore::AppCore(QObject *parent) : QObject(parent)
{
    qmlRegisterType<TaskModel>("TaskModel",1,0,"TaskModel");
}

AppCore::~AppCore()
{
}

