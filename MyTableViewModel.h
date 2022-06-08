#ifndef MYTABLEVIEWMODEL_H
#define MYTABLEVIEWMODEL_H

#include <QModelIndex>
#include "computerdata.h"

class MyTableViewModel : public QAbstractListModel
{
    Q_OBJECT
public:
    MyTableViewModel(QObject *parent = nullptr);
    ~MyTableViewModel();
public:
    int rowCount(const QModelIndex &) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    void populate(QList<ComputerData> *newValues);
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
public:
    void append(ComputerData value);
    void update(int idx, ComputerData value);
    void updateColor(const QModelIndex &index);
    void deleteRow(int idx);
    void insertAt(int idx, ComputerData value);
private:
    QList<ComputerData> *values;
    QList<QModelIndex> indexesList;
};

#endif // MYTABLEVIEWMODEL_H
