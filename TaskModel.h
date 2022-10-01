#ifndef TASKMODEL_H
#define TASKMODEL_H

#include <QAbstractListModel>
#include "Task.h"
#include "TaskManager.h"

class TaskModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit TaskModel(QObject *parent = nullptr);

    QHash<int, QByteArray> roleNames() const override;
    int rowCount(const QModelIndex &parent = {}) const override;
    QVariant data(const QModelIndex &index = {} , int role = Qt::DisplayRole) const override;

    Q_INVOKABLE bool append(const QString &text, const QString &time, const QString &progress);
    Q_INVOKABLE bool removeTask(const int& index);
    Q_INVOKABLE QString currentText(const int& index);
    Q_INVOKABLE QString currentTime(const int& index);
    Q_INVOKABLE double currentProgress(const int& index);
    Q_INVOKABLE void updateTask(const int& index, const QString &text, const QString &time, const QString &progress);

private:
    TaskManager taskManager;
    QList<Task> tasks;
    enum TaskRoles {
        TextRole = Qt::UserRole + 1, // номера для пользовотельских ролей начинаются с 256
        TimeRole,
        ProgressRole
    };

    bool updateTask();
};

#endif // TASKMODEL_H
