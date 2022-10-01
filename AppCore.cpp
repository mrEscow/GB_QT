#include "AppCore.h"
#include <QQmlEngine>
#include "TaskModel.h"

AppCore::AppCore(QObject *parent) : QObject(parent)
{
    qmlRegisterType<TaskModel>("EscowCompany",1,0,"TaskModel");
}

AppCore::~AppCore()
{
}

