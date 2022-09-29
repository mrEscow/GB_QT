#ifndef SELECTOR_H
#define SELECTOR_H

#include "DB_Types.h"
#include <QString>
#include <vector>
#include <QVariantList>
#include "Executor.h"

namespace DB
{
class Selector
{
public:
    DB_Result selectAll(const QString& tableName, std::vector<QVariantList>& returnData);
private:
    Executor executor;
private:
    QString generateQuery(const QString& tableName) const;
};
}

#endif // SELECTOR_H
