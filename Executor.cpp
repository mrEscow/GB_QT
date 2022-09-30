#include "Executor.h"
#include <QDebug>
#include <QSqlError>
namespace DB
{
Executor::Executor()
    :connectionManager{ConnectionManager::instance()}
{

}

std::pair<DB_Result, QSqlQuery> Executor::execute(const QString &queryText, const QVariantList &args)
{
    if(!connectionManager.isValid()){
        qCritical() << "Database is not valid, skip!";
        return {DB_Result::FAIL, QSqlQuery {}};
    }

    QSqlQuery query {queryText};
    for(int i = 0; i < args.size(); i++)
        query.bindValue(i, args[i]);

    DB_Result result {DB_Result::OK};

    if(!query.exec() && query.lastError().isValid()){
        qCritical() << query.lastError().text() << query.lastQuery();
        result = DB_Result::FAIL;
    }

    return {result, query};
}
}
