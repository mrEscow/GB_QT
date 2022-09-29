#include "Selector.h"
#include <QSqlQuery>
#include <QSqlRecord>

namespace DB
{

std::pair<DB_Result,std::vector<DB_Entry>> Selector::selectAll(const QString &tableName)
{
    QString query {generateQuery(tableName)};

    DB_Result result;
    QSqlQuery resultQuery;
    std::tie(result, resultQuery) = executor.execute(query);

    std::vector<DB_Entry> returnData;

    if(result == DB_Result::OK)
    {
        while(resultQuery.next())
        {
            const QSqlRecord& entryRecord {resultQuery.record()};
            QVariantList entryDate;

            for(int i = 0; i < entryRecord.count(); i++)
                entryDate.push_back(entryRecord.value(i));

            returnData.push_back(std::move(entryDate));
        }
    }

    return {result,returnData};
}

QString Selector::generateQuery(const QString &tableName) const
{
    QString query = "SELECT rowid, * FROM " + tableName;
    return query;
}

}
