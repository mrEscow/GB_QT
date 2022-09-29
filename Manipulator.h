#ifndef MANIPULATOR_H
#define MANIPULATOR_H

#include "DB_Types.h"
#include "Executor.h"

namespace DB {
class Manipulator
{
public:
    Manipulator();
    std::pair<DB_Result, DB_Index> insertRow(const QString& tableName, const QVariantList& recordData);
private:
    Executor executor;
private:
    QString generateBindString(size_t recordSize) const;
    QString generateInsertQuery(const QString& tableName, size_t recordSize) const;
};
}

#endif // MANIPULATOR_H
