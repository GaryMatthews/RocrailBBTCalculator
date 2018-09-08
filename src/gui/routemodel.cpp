

#include "routemodel.hpp"

#include <QModelIndex>

#include <QtGui/QIcon>

using BBTCalculator::Core::RouteList;
using BBTCalculator::Gui::RouteModel;

RouteModel::RouteModel(RouteList& lList, QObject* parent)
    : QAbstractTableModel(parent)
    , routeList{lList}
{
}

int RouteModel::rowCount(const QModelIndex& parent) const
{
    return static_cast<int>(routeList.size());
}

int RouteModel::columnCount(const QModelIndex& parent) const
{
    return static_cast<int>(RouteViewColumns::NUMBER_OF_COLUMNS);
}

QVariant RouteModel::data(const QModelIndex& index, int role) const
{
    if (not index.isValid()) // TODO: check index in range
        return QVariant();

    if (role == Qt::DisplayRole)
    {
        switch (static_cast<RouteViewColumns>(index.column()))
        {
        case RouteViewColumns::NAME:
            return routeList.at(static_cast<unsigned long>(index.row())).id;
        case RouteViewColumns::FROM_BLOCK:
            return routeList.at(static_cast<unsigned long>(index.row()))
                .fromBlock;
        case RouteViewColumns::TO_BLOCK:
            return routeList.at(static_cast<unsigned long>(index.row()))
                .toBlock;
        default:
            return QVariant();
        }
    }
    if (role == Qt::DecorationRole)
    {
        if (index.column() == static_cast<int>(RouteViewColumns::STRAIGHT))
        {
            const bool isStraight{
                routeList.at(static_cast<unsigned long>(index.row()))
                    .isCompletelyStraight};

            return isStraight ? QIcon::fromTheme("pass", QIcon(":/icons/pass"))
                              : QIcon::fromTheme("fail", QIcon(":/icons/fail"));
        }
        if (index.column() == static_cast<int>(RouteViewColumns::MAINLINE))
        {
            const bool isMainLine{
                routeList.at(static_cast<unsigned long>(index.row()))
                    .isOnlyMainline};

            return isMainLine ? QIcon::fromTheme("pass", QIcon(":/icons/pass"))
                              : QIcon::fromTheme("fail", QIcon(":/icons/fail"));
        }
    }
    return QVariant();
}

QVariant RouteModel::headerData(int section, Qt::Orientation orientation,
                                int role) const
{
    if (role != Qt::DisplayRole) // TODO: check index in rage
        return QVariant();

    if (orientation == Qt::Horizontal)
    {
        switch (static_cast<RouteViewColumns>(section))
        {
        case RouteViewColumns::MAINLINE:
            return tr("Mainline");
        case RouteViewColumns::NAME:
            return tr("Name");
        case RouteViewColumns::FROM_BLOCK:
            return tr("From Block");
        case RouteViewColumns::TO_BLOCK:
            return tr("To Block");
        case RouteViewColumns::STRAIGHT:
            return tr("Straight");
        default:
            return QVariant();
        }
    }
    return QVariant();
}
