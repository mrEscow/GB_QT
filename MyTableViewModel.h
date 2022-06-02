#ifndef MYTABLEVIEWMODEL_H
#define MYTABLEVIEWMODEL_H

#include <QModelIndex>
#include "computerdata.h"

class MyTableViewModel : public QAbstractListModel
{
public:
    MyTableViewModel(QObject *parent = nullptr);
    int rowCount(const QModelIndex &) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    void populate(QList<ComputerData> *newValues);
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
private:
    QList<ComputerData> *values;


};

#endif // MYTABLEVIEWMODEL_H
