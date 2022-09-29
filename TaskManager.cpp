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
}

std::pair<bool, QList<Task> > TaskManager::requestTaskBrowse()
{
    DB::DB_Result result;
    std::vector<DB::DB_Entry> entries;
    std::tie(result, entries) = processor->requestTableDate(DB::DB_Tables::TASK);

    return {result == DB::DB_Result::OK, transform(entries)};
}

bool TaskManager::append(Task task)
{
    DB::DB_Result result;
    DB::DB_Entry entry;

    entry.push_back(task.getText());
    entry.push_back(task.getTime());
    entry.push_back(task.getProgress());

    result = processor->insertRowDate(DB::DB_Tables::TASK,entry);

    return result == DB::DB_Result::OK;
}
