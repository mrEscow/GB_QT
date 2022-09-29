#ifndef CONNECTIONMANAGER_H
#define CONNECTIONMANAGER_H
#include <QObject>
#include <memory>

namespace DB
{
class ConnectionManager
{
public:
    Q_DISABLE_COPY(ConnectionManager);
    ~ConnectionManager();
    static ConnectionManager& instance();
    bool isValid() const;
private:
    ConnectionManager();
    struct ConnectionManagerPrivate;
    std::unique_ptr<ConnectionManagerPrivate> d;
};
}

#endif // CONNECTIONMANAGER_H
