//
// Created by markus on 06.10.18.
//

#include "gui/imagesortfilterproxymodel.hpp"

#include <QIcon>

#include "gui/bbtmodel.hpp"

using BBTCalculator::Gui::ImageSortFilterProxyModel;
using BBTCalculator::Gui::BBTModel;

ImageSortFilterProxyModel::ImageSortFilterProxyModel(QObject* parent)
    : QSortFilterProxyModel(parent)
{
}

bool ImageSortFilterProxyModel::lessThan(const QModelIndex& source_left,
                                         const QModelIndex& source_right) const
{
    if (source_left.data(Qt::DecorationRole).type() == QVariant::Icon)
    {
        return source_left.data(Qt::ToolTipRole) >
               source_right.data(Qt::ToolTipRole);
    }
    else {
        return QSortFilterProxyModel::lessThan(source_left, source_right);
    }


}
