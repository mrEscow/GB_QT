#ifndef SELECTOR_H
#define SELECTOR_H

#include "DB_Types.h"
#include <QString>
#include <vector>
#include "Executor.h"

namespace DB
{
class Selector
{
public:
    std::pair<DB_Result,std::vector<DB_Entry>> selectAll(const QString& tableName);
private:
    Executor executor;
private:
    QString generateQuery(const QString& tableName) const;
};
}

#endif // SELECTOR_H
