#pragma once

#include <QVariantList>

namespace DB
{
enum class DB_Result
{
    OK,
    FAIL
};

enum class DB_Tables
{
    TASK
};

enum class DB_Stage
{
    OK,
    ERROR_NO_DRIVER,
    ERROR_WORKSPACE,
    ERROR_TABLES,
    ERROR_OPENING
};

using DB_Entry = QVariantList;
using DB_Index = int;
}

