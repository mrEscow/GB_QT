#ifndef DB_TYPES_H
#define DB_TYPES_H

namespace DB
{
enum class DB_Result
{
    Ok,
    FAIL
};

enum class DB_Tables
{
    CONTACTS
};

enum class DB_Stage
{
    OK,
    ERROR_NO_DRIVER,
    ERROR_WORKSPACE,
    ERROR_TABLES,
    ERROR_OPENING
};
}

#endif // DB_TYPES_H
