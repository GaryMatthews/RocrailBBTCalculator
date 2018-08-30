

#include "blockmodel.hpp"

#include <QModelIndex>
#include <QtGui/QIcon>

using BBTCalculator::Core::BlockList;
using BBTCalculator::Gui::BlockModel;

BlockModel::BlockModel(BlockList& lList, QObject* parent)
    : QAbstractTableModel(parent)
    , blockList{lList}
{
}

int BlockModel::rowCount(const QModelIndex& parent) const
{
    return static_cast<int>(blockList.size());
}

int BlockModel::columnCount(const QModelIndex& parent) const
{
    return static_cast<int>(BlockViewColumns::NUMBER_OF_COLUMNS);
}

QVariant BlockModel::data(const QModelIndex& index, int role) const
{
    if (not index.isValid()) // TODO: check index in range
        return QVariant();

    if (role == Qt::DisplayRole)
    {
        switch (static_cast<BlockViewColumns>(index.column()))
        {
        case BlockViewColumns::NAME:
            return blockList.at(static_cast<unsigned long>(index.row())).name;
        case BlockViewColumns::LEN:
            return blockList.at(static_cast<unsigned long>(index.row())).length;
        default:
            return QVariant();
        }
    }
    if (role == Qt::DecorationRole &&
        index.column() == static_cast<int>(BlockViewColumns::MAINLINE))
    {
        const bool isMainLine{
            blockList.at(static_cast<unsigned long>(index.row())).isMainLine};

        return isMainLine ? QIcon::fromTheme("pass", QIcon(":/icons/pass"))
                          : QIcon::fromTheme("fail", QIcon(":/icons/fail"));
    }
    return QVariant();
}

QVariant BlockModel::headerData(int section, Qt::Orientation orientation,
                                int role) const
{
    if (role != Qt::DisplayRole) // TODO: check index in rage
        return QVariant();

    if (orientation == Qt::Horizontal)
    {
        switch (static_cast<BlockViewColumns>(section))
        {
        case BlockViewColumns::MAINLINE:
            return tr("Mainline");
        case BlockViewColumns::NAME:
            return tr("Name");
        case BlockViewColumns::LEN:
            return tr("Length");
        default:
            return QVariant();
        }
    }
    return QVariant();
}

Qt::ItemFlags BlockModel::flags(const QModelIndex& index) const
{
    return QAbstractTableModel::flags(index);
}
