#include "Task.h"


Task::Task(const QString &task, const QString &time, const QString &progress)
{
    this->task = std::move(task);
    this->time = std::move(time);
    this->prog = std::move(progress);
}

QString Task::getTask() const
{
    return task;
}

QString Task::getTime() const
{
    return time;
}

QString Task::getProgress() const
{
    return prog;
}
