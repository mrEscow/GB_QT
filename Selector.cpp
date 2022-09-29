#include "Selector.h"
#include <QSqlQuery>
#include <QSqlRecord>

namespace DB
{

DB_Result Selector::selectAll(const QString &tableName, std::vector<QVariantList> &returnData)
{
    QString query {generateQuery(tableName)};

    DB_Result result;
    QSqlQuery resultQuery;
    std::tie(result, resultQuery) = executor.execute(query);

    if(result == DB_Result::OK)
    {
        returnData.clear();
        while(resultQuery.next())
        {
            const QSqlRecord& entryRecord {resultQuery.record()};
            QVariantList entryDate;

            for(int i = 0; i < entryRecord.count(); i++)
                entryDate.push_back(entryRecord.value(i));

            returnData.push_back(std::move(entryDate));
        }
    }

    return result;
}

QString Selector::generateQuery(const QString &tableName) const
{
    QString query {"SELECT rowid, * FROM " + tableName};
    return query;
}

}
