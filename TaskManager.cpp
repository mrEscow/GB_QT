#include "TaskManager.h"
#include "Processor.h"
#include "DB_Types.h"

TaskManager::TaskManager()
    : processor {new DB::Processor {}}
{
}

TaskManager::~TaskManager()
{
}

namespace
{
    QList<Task> transform(std::vector<DB::DB_Entry> source)
    {
        QList<Task> target;
        std::transform(source.begin(), source.end(), std::back_inserter(target),
                       [](const DB::DB_Entry& entry){
                           return Task {entry[1].toString(), entry[2].toString(), entry[3].toString()};
        });
        return target;
    }

    DB::DB_Entry transform(const Task& source)
    {
        DB::DB_Entry target;
        target.push_back(source.getText());
        target.push_back(source.getTime());
        target.push_back(source.getProgress());
        return target;
    }
}

std::pair<bool, QList<Task> > TaskManager::requestTaskBrowse()
{
    DB::DB_Result result;
    std::vector<DB::DB_Entry> entries;
    std::tie(result, entries) = processor->requestTableDate(DB::DB_Tables::TASKS);
    return {result == DB::DB_Result::OK, transform(entries)};
}

bool TaskManager::append(const Task &task)
{
    DB::DB_Result result;
    DB::DB_Entry entry = transform(task);
    result = processor->insertRowDate(DB::DB_Tables::TASKS, entry);
    return result == DB::DB_Result::OK;
}

bool TaskManager::removeTask(const Task &task)
{
    DB::DB_Result result;
    DB::DB_Entry entry = transform(task);
    result = processor->removeRowDate(DB::DB_Tables::TASKS, entry);
    return result == DB::DB_Result::OK;
}
