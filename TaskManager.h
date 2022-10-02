#ifndef TASKMANAGER_H
#define TASKMANAGER_H

#include <utility>
#include <memory>
#include <QList>
#include "Task.h"

namespace DB {
class Processor;
}

class TaskManager
{
public:
    TaskManager();
    ~TaskManager();
    std::pair<bool, QList<Task>> requestTaskBrowse();
    bool append(const Task& task);
    bool removeTask(const Task &task);
    bool updateTask(const Task &oldTask,const Task &newTask);
private:
    std::unique_ptr<DB::Processor> processor;
};

#endif // TASKMANAGER_H
