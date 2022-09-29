#include "TaskModel.h"
#include <QDebug>

TaskModel::TaskModel(QObject *parent)
    : QAbstractListModel{parent}
{
    const bool upadateResult{updateTask()};

    if(!upadateResult)
        qWarning() << "Update Task is failed!";
}

QHash<int, QByteArray> TaskModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[TaskRoles::TextRole] = "text";
    roles[TaskRoles::TimeRole] = "time";
    roles[TaskRoles::ProgressRole] = "progress";

    return roles;
}

int TaskModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return tasks.size();
}

QVariant TaskModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid() || index.row() > rowCount(index))
        return {};

    const Task& task {tasks.at(index.row())};

    switch(role){
        case TextRole:
            return QVariant::fromValue(task.getText());
        case TimeRole:
            return QVariant::fromValue(task.getTime());
        case ProgressRole:
            return QVariant::fromValue(task.getProgress());
        default:
            return true;
        }
}

bool TaskModel::append(const QString &text, const QString &time, const QString &progress)
{
    bool requestResult = taskManager.append(Task(text,time,progress));

    if(requestResult){
        beginInsertRows(QModelIndex(), tasks.size(), tasks.size());
            tasks.append(Task(text,time,progress));
        endInsertRows();

        emit dataChanged(createIndex(0,0), createIndex(tasks.size(),0));
    }

    return requestResult;
}

void TaskModel::removeTask(const int &index)
{
    beginRemoveRows(QModelIndex(), index, index);
        tasks.removeAt(index);
    endRemoveRows();

    emit dataChanged(createIndex(0,0), createIndex(tasks.size(),0));
}

bool TaskModel::updateTask()
{
    bool requestResult{false};
    QList<Task> tasksResult;
    std::tie(requestResult, tasksResult) = taskManager.requestTaskBrowse();
    if(requestResult){
        tasks.swap(tasksResult);
        emit dataChanged(createIndex(0,0), createIndex(tasks.size(),0));
    }

    return requestResult;
}
