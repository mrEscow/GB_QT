#include "TaskModel.h"

TaskModel::TaskModel(QObject *parent)
    : QAbstractListModel{parent}
{

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
    if(index.isValid() || index.row() > rowCount(index))
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
