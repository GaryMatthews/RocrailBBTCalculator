

#include "locmodel.hpp"

#include <QModelIndex>
#include <QtGui/QIcon>

using BBTCalculator::Core::LocList;
using BBTCalculator::Gui::LocModel;

LocModel::LocModel(LocList& lList, QObject* parent)
    : QAbstractTableModel(parent)
    , locList{lList}
{
}

int LocModel::rowCount(const QModelIndex& parent) const
{
    return static_cast<int>(locList.size());
}

int LocModel::columnCount(const QModelIndex& parent) const
{
    return NUMBER_OF_COLUMNS;
}

QVariant LocModel::data(const QModelIndex& index, int role) const
{
    if (not index.isValid()) // TODO: check index in range
        return QVariant();

    if (role == Qt::DisplayRole)
    {
        switch (index.column())
        {
        case LocViewColumns::NAME:
            return locList.at(static_cast<unsigned long>(index.row())).name;
        case LocViewColumns::BBT_STEPS:
            return locList.at(static_cast<unsigned long>(index.row())).bbtSteps;
        case LocViewColumns::V_MIN:
            return locList.at(static_cast<unsigned long>(index.row())).v_min;
        case LocViewColumns::V_MID:
            return locList.at(static_cast<unsigned long>(index.row())).v_mid;
        case LocViewColumns::V_CRU:
            return locList.at(static_cast<unsigned long>(index.row())).v_cru;
        default:
            return QVariant();
        }
    }
    if (role == Qt::DecorationRole)
    {
        const bool useBBT{
            locList.at(static_cast<unsigned long>(index.row())).useBBT};
        switch (index.column())
        {
        case LocViewColumns::BBT:
            return useBBT ? QIcon::fromTheme("pass", QIcon(":/icons/pass"))
                          : QIcon::fromTheme("fail", QIcon(":/icons/fail"));
        default:
            return QVariant();
        }
    }
    return QVariant();
}

QVariant LocModel::headerData(int section, Qt::Orientation orientation,
                              int role) const
{
    if (role != Qt::DisplayRole) // TODO: check index in rage
        return QVariant();

    if (orientation == Qt::Horizontal)
    {
        switch (section)
        {
        case LocViewColumns::BBT:
            return tr("BBT");
        case LocViewColumns::NAME:
            return tr("Name");
        case LocViewColumns::BBT_STEPS:
            return tr("BBT Steps");
        case LocViewColumns::V_MIN:
            return tr("V min");
        case LocViewColumns::V_MID:
            return tr("V mid");
        case LocViewColumns::V_CRU:
            return tr("V cru");
        default:
            return QVariant();
        }
    }
    return QVariant();
}

Qt::ItemFlags LocModel::flags(const QModelIndex& index) const
{
    if (index.isValid() &&
        not locList.at(static_cast<unsigned long>(index.row())).useBBT)
    {
        return QAbstractTableModel::flags(index) & ~Qt::ItemIsEnabled;
    }
    return QAbstractTableModel::flags(index);
}
