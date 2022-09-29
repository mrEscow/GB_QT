#ifndef EXECUTOR_H
#define EXECUTOR_H

#include "DB_Types.h"
#include "ConnectionManager.h"
#include <QSqlQuery>

namespace DB
{
class Executor
{
public:
    Executor();
    Q_DISABLE_COPY(Executor)
    std::pair<DB_Result, QSqlQuery> execute(const QString& queryText, const QVariantList& args = {});
private:
    ConnectionManager& connectionManager;
};
}

#endif // EXECUTOR_H
