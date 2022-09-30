#include "Processor.h"
#include "Selector.h"
#include "Manipulator.h"
#include "DB_Mapper.h"
#include <QDebug>

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
    const auto& result {d->manipulator.insertRow(TableMapper.at(table), entry)};
    return result.first;
}

DB_Result Processor::removeRowDate(DB_Tables table, DB_Entry entry)
{
    const auto& result {d->manipulator.removeRow(TableMapper.at(table), entry)};
    return result.first;
}
}
