#include "MyTableViewModel.h"

MyTableViewModel::MyTableViewModel(QObject *parent)
    : QAbstractListModel(parent)
{
    values = new QList<ComputerData>();

}

MyTableViewModel::~MyTableViewModel()
{
    delete values;
}

int MyTableViewModel::rowCount(const QModelIndex &) const
{
    return values->count();
}

int MyTableViewModel::columnCount(const QModelIndex &) const
{
    return 3;
}

QVariant MyTableViewModel::data( const QModelIndex &index, int role ) const
{

    QVariant value;

        switch ( role )
        {
            case Qt::DisplayRole: //string
            {
                switch (index.column()) {
                    case 0: {
                        value = this->values->at(index.row()).getName();
                        break;
                    }
                    case 1: {
                        value = this->values->at(index.row()).getIp();
                        break;
                    }
                    case 2: {
                        value = this->values->at(index.row()).getMac();
                        break;
                    }
                }
            }
            break;

            case Qt::UserRole: //data
            {
                value = this->values->at(index.row()).getName();
            }
            break;

            default:
                break;
        }

    return value;
}

void MyTableViewModel::populate(QList<ComputerData> *newValues)
{
    int idx = this->values->count();
    this->beginInsertRows(QModelIndex(), 1, idx);
        this->values = newValues;
    endInsertRows();
}

QVariant MyTableViewModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        switch (section) {
        case 0:
            return QString("Имя компьютера");
        case 1:
            return QString("IP адрес");
        case 2:
            return QString("MAC адрес");
        }
    }
    return QVariant();
}

void MyTableViewModel::append(ComputerData value)
{
    int newRow = this->values->count()+1;

    this->beginInsertRows(QModelIndex(), newRow, newRow);
        values->append(value);
    endInsertRows();
}

void MyTableViewModel::update(int idx, ComputerData value)
{
    (*this->values)[idx] = value;

    QModelIndex item_idx_s = this->index(idx,0);
    QModelIndex item_idx_e = this->index(idx,this->columnCount(QModelIndex()));

    emit this->dataChanged(item_idx_s ,item_idx_e );
}

void MyTableViewModel::deleteRow(int idx)
{
    this->beginRemoveRows(QModelIndex(), idx,idx);

        (*this->values).removeAt(idx);

    this->endRemoveRows();
}

void MyTableViewModel::insertAt(int idx, ComputerData value)
{

    int newRow = idx;

    this->beginInsertRows(QModelIndex(), newRow, newRow);

        values->insert(newRow,value);

    endInsertRows();
}
