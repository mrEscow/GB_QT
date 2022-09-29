#include "ConnectionManager.h"
#include "DB_Types.h"
#include "qdir.h"
#include <QSqlDatabase>
#include <QDebug>
#include <QStandardPaths>
#include <QDir>
#include <QSqlError>
#include <QSqlQuery>

namespace DB{
namespace
{
    class DBCloser
    {
    public:
        void operator()(QSqlDatabase* db)
        {
            db->close();
            QSqlDatabase::removeDatabase(QSqlDatabase::defaultConnection);
            delete db;
        }
    };
}

struct ConnectionManager::ConnectionManagerPrivate
{
    std::unique_ptr<QSqlDatabase, DBCloser> database;
    QString dbPath;
    bool isValid {true};
    DB_Stage stage {DB_Stage::OK};

    bool setup();
    bool setupWorkspace();
    bool setupTables();
};

ConnectionManager &ConnectionManager::instance()
{
    static ConnectionManager instance;
    return instance;
}

bool ConnectionManager::isValid() const
{
    return d->isValid;
}

ConnectionManager::ConnectionManager()
    : d{new ConnectionManagerPrivate}
{
    const bool setupResult = d->setup();
    d->isValid = setupResult;
}

ConnectionManager::~ConnectionManager()
{
}

bool ConnectionManager::ConnectionManagerPrivate::setup()
{
    static const QString driver {"QSQLITE"};

    if(!QSqlDatabase::isDriverAvailable(driver)){
        stage = DB_Stage::ERROR_NO_DRIVER;
        qCritical() << "Driver" << driver << "is not available!";
        return false;
    }

    if(!setupWorkspace()){
        stage = DB_Stage::ERROR_WORKSPACE;
        qCritical() << "Workspace setup failed!";
        return false;
    }

    database.reset(new QSqlDatabase {QSqlDatabase::addDatabase(driver)});
    database->setDatabaseName(dbPath);

    qDebug() << "Database name: " << database->databaseName();

    if(!database->open()){
        stage = DB_Stage::ERROR_OPENING;
        qCritical() << "Error in opening DB" << database->databaseName()
                    << "reason " << database->lastError().text();
        return false;
    }

    return setupTables();
}

bool ConnectionManager::ConnectionManagerPrivate::setupWorkspace()
{
    static const QString databaseName {"TaskDB"};

    const QString location {QStandardPaths::writableLocation(QStandardPaths::AppDataLocation)};
    const QString fullPath {location + "/" + databaseName + ".db"};

    dbPath = fullPath;

    QDir dbDirectory {location};
    if(!dbDirectory.exists()){
        const bool creationResult {dbDirectory.mkdir(location)};
        qInfo() << "DB directory not exist, creating result : " << creationResult;
    }

    qDebug() << "Data path: " << fullPath;

    return dbDirectory.exists();
}

bool ConnectionManager::ConnectionManagerPrivate::setupTables()
{
    bool result {true};

    std::vector<QSqlQuery> creationQueries{
        QSqlQuery{
            "CREATE TABLE IF NOT EXISTS Tasks"
            "("
            "Text TEXT,"
            "Time TEXT,"
            "Progress TEXT"
            ")"
        }
    };

    for(auto& query: creationQueries)
        if(!query.exec()){
            result = false;
            stage = DB_Stage::ERROR_TABLES;
            qWarning() << "Table creation failed. Reason:"
                       << query.lastError() << "; Query: " << query.lastQuery();
        }
        else{
            qInfo() <<" Table successfuly created! Query: \n" << query.lastQuery();
        }

    return result;
}

}
