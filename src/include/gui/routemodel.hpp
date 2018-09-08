

#pragma once

#include <QtCore/QAbstractTableModel>

#include "core/datastructs.hpp"

namespace BBTCalculator
{
    namespace Gui
    {
        enum class RouteViewColumns
        {
            MAINLINE = 0,
            NAME,
            FROM_BLOCK,
            TO_BLOCK,
            STRAIGHT,
            NUMBER_OF_COLUMNS
        };

        class RouteModel : public QAbstractTableModel
        {
        public:
            explicit RouteModel(Core::RouteList& lList,
                                QObject* parent = nullptr);

            int rowCount(const QModelIndex& parent) const override;

            int columnCount(const QModelIndex& parent) const override;

            QVariant data(const QModelIndex& index, int role) const override;

            QVariant headerData(int section, Qt::Orientation orientation,
                                int role) const override;

        private:
            Core::RouteList& routeList;
        };
    } // namespace Gui
} // namespace BBTCalculator
