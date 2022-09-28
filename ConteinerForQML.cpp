#include "ConteinerForQML.h"


ConteinerForQML::ConteinerForQML(const QString &task, const QString &time, const QString &prog)
{
    this->task = std::move(task);
    this->time = std::move(time);
    this->prog = std::move(prog);
}

QList<QString> ConteinerForQML::getDatas()
{
    QList<QString> list;
    return  list << task << time << prog;
}

QString ConteinerForQML::getTask() const
{
    return task;
}

QString ConteinerForQML::getTime() const
{
    return time;
}

QString ConteinerForQML::getPprog() const
{
    return prog;
}
