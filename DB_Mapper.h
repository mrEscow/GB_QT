#ifndef DB_MAPPER_H
#define DB_MAPPER_H

#include "DB_Types.h"

namespace DB
{
static const std::map<DB_Tables, QString> TableMapper {
    {DB_Tables::TASKS, "Tasks"}
};

static const std::map<QString, QString> TableMapping {
    {"Tasks","Text, Time, Progress"}
};

}

#endif // DB_MAPPER_H
