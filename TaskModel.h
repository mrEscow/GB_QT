#ifndef TASKMODEL_H
#define TASKMODEL_H

#include <QAbstractListModel>
#include "Task.h"
#include "TaskReader.h"

class TaskModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit TaskModel(QObject *parent = nullptr);

    QHash<int, QByteArray> roleNames() const override;
    int rowCount(const QModelIndex &parent = {}) const override;
    QVariant data(const QModelIndex &index = {} , int role = Qt::DisplayRole) const override;

    Q_INVOKABLE void append(const QString &text, const QString &time, const QString &prog);

private:
    TaskReader taskReader;
    QList<Task> tasks;
    enum TaskRoles {
        TextRole = Qt::UserRole + 1, // номера для пользовотельских ролей начинаются с 256
        TimeRole,
        ProgressRole
    };

    bool updateTask();
};

#endif // TASKMODEL_H
