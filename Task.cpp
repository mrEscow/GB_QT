#include "Task.h"


Task::Task(const QString &text, const QString &time, const QString &progress)
{
    this->text = std::move(text);
    this->time = std::move(time);
    this->prog = std::move(progress);
}

QString Task::getText() const
{
    return text;
}

QString Task::getTime() const
{
    return time;
}

QString Task::getProgress() const
{
    return prog;
}
