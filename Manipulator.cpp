#include "Manipulator.h"
#include "DB_Mapper.h"
#include <sstream>
#include <QDebug>

namespace DB {
Manipulator::Manipulator()
{

}

std::pair<DB_Result, DB_Index> Manipulator::insertRow(const QString &tableName, const DB_Entry &recordData)
{
    const QString& query {generateInsertQuery(tableName,recordData.size())};
    const auto& result {executor.execute(query, recordData)};
    return {result.first, result.second.lastInsertId().toInt()};
}

QString Manipulator::generateInsertQuery(const QString &tableName, size_t recordSize) const
{
    QString query {"INSERT INTO " + tableName + " (" + TableMapping.at(tableName) + ") " + "VALUES ("};
    query += generateBindString(recordSize);
    query += ")";
    return query;
}

std::pair<DB_Result, DB_Index> Manipulator::removeRow(const QString &tableName, const DB_Entry &removeData)
{
    const QString& query {generateDeleteQuery(tableName,removeData)};
    const auto& result {executor.execute(query)};
    return {result.first, result.second.lastInsertId().toInt()};
}

QString Manipulator::generateDeleteQuery(const QString &tableName, DB_Entry removeData) const
{
    QString query {"DELETE FROM " + tableName + " WHERE "};
    QString bindString = TableMapping.at(tableName);
    bindString += generateBindString(tableName,removeData);
    query += bindString;
    return query;
}

std::pair<DB_Result, DB_Index> Manipulator::updateRow(const QString &tableName, const DB_Entry &oldData, const DB_Entry &newData)
{
    QString query {generateUpdateQuery(tableName,oldData,newData)};
    const auto& result {executor.execute(query)};
    return {result.first, result.second.lastInsertId().toInt()};
}

QString Manipulator::generateUpdateQuery(const QString &tableName, const DB_Entry &oldData, const DB_Entry &newData) const
{
    QString query {"UPDATE " + tableName};
    query += " SET ";
    query += generateBindString(tableName,newData,",");
    query += " WHERE ";
    query += generateBindString(tableName,oldData);
    return query;
}

QString Manipulator::generateBindString(size_t recordSize) const
{
    std::ostringstream bindings;
    std::fill_n(std::ostream_iterator<std::string>(bindings),
                recordSize,
                "?,");
    std::string bindString = bindings.str();
    bindString.pop_back(); // Убираем последнюю запятую
    return QString::fromStdString(bindString);
}

QString Manipulator::generateBindString(const QString &tableName, const DB_Entry &data, const QString& simbol) const
{
    QString defSymbol = "AND";
    QString bindString = TableMapping.at(tableName);
    int count = 0;
    for(int i = 0, j = 0; i < bindString.size(); i++){
        count++;
        if(bindString[i] == ','){
            bindString[i] = ' ';
            bindString.insert(count - 1 , " = '" + data[j].toString() + "' " + defSymbol);
            j++;
        }
    }
    if(simbol != defSymbol)
        bindString.replace(defSymbol,simbol);
    bindString += " = '" + data[data.size() - 1].toString() + "'";
    return bindString;
}
}
