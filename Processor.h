#ifndef PROCESSOR_H
#define PROCESSOR_H

#include "DB_Types.h"
#include <memory>

namespace DB
{
class Processor
{
public:
    Processor();
    ~Processor();
    std::pair<DB_Result,std::vector<DB_Entry>> requestTableDate(DB_Tables table);
    DB_Result insertRowDate(DB_Tables table, DB_Entry entry);
    DB_Result removeRowDate(DB_Tables table, DB_Entry entry);
    DB_Result updareRowDate(DB_Tables table, DB_Entry oldEntry, DB_Entry newEntry);

private:
    struct ProcessorPrivate;
    std::unique_ptr<ProcessorPrivate> d;
};
}

#endif // PROCESSOR_H
