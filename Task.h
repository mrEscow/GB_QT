#ifndef TASK_H
#define TASK_H
#include <QString>
#include <QList>

class Task
{
public:
    Task(const QString &text, const QString &time, const QString &prog);
    QString getText() const;
    QString getTime() const;
    QString getProgress() const;
private:
    QString text;
    QString time;
    QString prog;
};

#endif // TASK_H
