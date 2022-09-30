#ifndef MANIPULATOR_H
#define MANIPULATOR_H

#include "DB_Types.h"
#include "Executor.h"

namespace DB {
class Manipulator
{
public:
    Manipulator();
    std::pair<DB_Result, DB_Index> insertRow(const QString& tableName, const DB_Entry& recordData);
    std::pair<DB_Result, DB_Index> removeRow(const QString& tableName, const DB_Entry& removeData);
private:
    Executor executor;
private:
    QString generateBindString(size_t recordSize) const;
    QString generateInsertQuery(const QString& tableName, size_t recordSize) const;
    QString generateDeleteQuery(const QString& tableName, DB_Entry removeData) const;
};
}

#endif // MANIPULATOR_H
