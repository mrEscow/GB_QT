#ifndef TASK_H
#define TASK_H
#include <QString>
#include <QList>

class Task
{
public:
    Task(const QString &task, const QString &time, const QString &prog);
    QString getTask() const;
    QString getTime() const;
    QString getProgress() const;
private:
    QString task;
    QString time;
    QString prog;
};

#endif // TASK_H
