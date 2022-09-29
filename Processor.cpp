#include "Processor.h"
#include "Selector.h"
#include "Manipulator.h"
#include "DB_Mapper.h"

namespace DB
{
struct Processor::ProcessorPrivate
{
    Selector selector;
    Manipulator manipulator;
};

Processor::Processor()
    : d {new ProcessorPrivate {}}
{
}

Processor::~Processor()
{
}

std::pair<DB_Result, std::vector<DB_Entry>> Processor::requestTableDate(DB_Tables table)
{
    const auto& result {d->selector.selectAll(TableMapper.at(table))};
    return result;
}

DB_Result Processor::insertRowDate(DB_Tables table, DB_Entry entry)
{
    d->manipulator.insertRow("Task",{{"X","X2","X3"}});
    const auto& result {d->manipulator.insertRow(TableMapper.at(table), entry)};
    return result.first;
}
}
