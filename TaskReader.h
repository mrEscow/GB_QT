#ifndef TASKREADER_H
#define TASKREADER_H

#include <utility>
#include <QList>
#include "Task.h"

class TaskReader
{
public:
    std::pair<bool, QList<Task>> requestTaskBrowse();
};

#endif // TASKREADER_H
