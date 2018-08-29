

#include "locmodel.hpp"

#include <QModelIndex>

using BBTCalculator::Core::LocList;
using BBTCalculator::Gui::LocModel;

LocModel::LocModel(LocList& lList, QObject* parent) :
    QAbstractTableModel(parent),
    locList{lList}
{

}

int LocModel::rowCount(const QModelIndex& parent) const
{
    return static_cast<int>(locList.size());
}

int LocModel::columnCount(const QModelIndex& parent) const
{
    return 1;
}

QVariant LocModel::data(const QModelIndex& index, int role) const
{
    if (not index.isValid() || role != Qt::DisplayRole) // TODO: check index in range
        return QVariant();

    switch (index.column())
    {
        case 0:
            return locList.at(static_cast<unsigned long>(index.row())).name;
        default:
            return QVariant();
    }
}

QVariant LocModel::headerData(int section, Qt::Orientation orientation, int role) const
{

    if (role != Qt::DisplayRole) // TODO: check index in rage
        return QVariant();

    if (orientation == Qt::Horizontal)
    {
        switch (section)
        {
        case 0:
            return tr("Name");
        default:
            return QVariant();
        }
    }
    return QVariant();
}
