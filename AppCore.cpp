#include "AppCore.h"
#include "qdebug.h"
#include <QFile>
#include <QDataStream>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonValue>

AppCore::AppCore(QObject *parent) : QObject(parent)
{
    fileName = "Tasks.json";
    load();
}

AppCore::~AppCore()
{
    save();
}

void AppCore::setDate(const QString &task, const QString &time, const QString &prog)
{
     dateConteiners.push_back(Task(task,time,prog));
}

QStringList AppCore::getDates()
{
    QStringList dates;

    for(auto& conteiner: dateConteiners)
        dates << conteiner.getTask() << conteiner.getTime() << conteiner.getProgress();
    return dates;
}

void AppCore::removeDate(const int& index)
{
    dateConteiners.removeAt(index);
}

void AppCore::save()
{
    QFile file(fileName);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QVariantMap variantMap;
    QJsonArray jsonArray;

    for(auto& conteiner: dateConteiners){
        variantMap.insert("task", conteiner.getTask());
        variantMap.insert("time", conteiner.getTime());
        variantMap.insert("prog", conteiner.getProgress());
        jsonArray.append(QJsonObject::fromVariantMap(variantMap));
    }

    file.write(QJsonDocument(jsonArray).toJson());
    file.close();
}

void AppCore::load()
{
    QFile file(fileName);;
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QString val;
    val = file.readAll();
    file.close();

    QJsonArray jsonArray = QJsonDocument::fromJson(val.toUtf8()).array();

    for(auto json: jsonArray){
        QString task = json.toObject()["task"].toString();
        QString time = json.toObject()["time"].toString();
        QString prog = json.toObject()["prog"].toString();
        dateConteiners.push_back(Task(task,time,prog));
    }
}
